"""
Sample specified number of samples from problem file
"""
import argparse, os, json, random


def sample_random(
    sample_from,
    include_all,
    num_training,
    num_testing
):
    sample_from_ids = [i for i in range(len(sample_from))]
    random.shuffle(sample_from_ids)
    # Initialize training and testing sets with guarantee includes
    training = [include_all[i] for i in range( min(len(include_all), num_training) )] # Add include_all
    testing = [include_all[i] for i in range( min(len(include_all), num_testing) )]
    # Sample from examples to fill up training
    while (len(training) < num_training) and (len(sample_from_ids) > 0):
        training.append(sample_from[sample_from_ids.pop()])
    while (len(testing) < num_testing) and (len(sample_from_ids) > 0):
        testing.append(sample_from[sample_from_ids.pop()])
    return {"training": training, "testing": testing}

def sample_even_output(
    sample_from,
    include_all,
    num_training,
    num_testing
):
    # Add "include all" examples to both training and testing sets
    training = [include_all[i] for i in range( min(len(include_all), num_training) )]
    testing = [include_all[i] for i in range( min(len(include_all), num_testing) )]

    # Identify all output fields (does not assume that all examples have same output fields)
    output_fields = set()
    for example in sample_from:
        example = json.loads(example)
        for field in example:
            if "output" in field:
                output_fields.add(field)
    output_fields = sorted(list(output_fields))

    # Categorize all example ids
    output_ids = {}
    for example_id in range(len(sample_from)):
        example = json.loads(sample_from[example_id])
        output_key = "_".join([example[field] for field in output_fields])
        if not output_key in output_ids:
            output_ids[output_key] = []
        output_ids[output_key].append(example_id)

    # Shuffle all categories of example ids
    for output_key in output_ids:
        random.shuffle(output_ids[output_key])
    output_keys = list(output_ids.keys())
    # Evenly sample examples from "sample_from" based on output category
    num_excluded_examples = len(sample_from)
    current_output_type = 0
    # Add to training set
    while (len(training) < num_training) and (num_excluded_examples > 0):
        # identify an output type
        cur_key_id = current_output_type % len(output_keys)
        cur_key = output_keys[cur_key_id]
        # If we've already included all examples with this output type, skip over it
        if len(output_ids[cur_key]) == 0:
            current_output_type += 1
            continue
        training.append(
            sample_from[output_ids[cur_key].pop()]
        )
        current_output_type += 1
        num_excluded_examples -= 1
    # Add to testing set
    while (len(testing) < num_testing) and (num_excluded_examples > 0):
        # identify an output type
        cur_key_id = current_output_type % len(output_keys)
        cur_key = output_keys[cur_key_id]
        # If we've already included all examples with this output type, skip over it
        if len(output_ids[cur_key]) == 0:
            current_output_type += 1
            continue
        testing.append(
            sample_from[output_ids[cur_key].pop()]
        )
        current_output_type += 1
        num_excluded_examples -= 1
    return {"training": training, "testing": testing}

problem_samplers = {
    "none": sample_random,
    "small-or-large": sample_even_output,
    "median": sample_random,
    "grade": sample_even_output
}

def main():
    parser = argparse.ArgumentParser(description="Sample examples.")
    parser.add_argument("--sample_from", type=str, help="Input file containing examples (1 per line)")
    parser.add_argument("--include_all", default=None, type=str, help="Auto-include examples")
    parser.add_argument("--output_prefix", default=None, type=str, help="Name of output file")
    parser.add_argument("--problem", default="none", type=str, help="Use problem-specific sampler")
    parser.add_argument("--num_training", type=int, default=10, help="Number of training examples")
    parser.add_argument("--num_testing", type=int, default=10, help="Number of testing examples")

    args = parser.parse_args()
    sample_from = args.sample_from
    include_all = args.include_all
    output_prefix = args.output_prefix
    problem = args.problem
    num_training = args.num_training
    num_testing = args.num_testing

    # Identify appropriate sample function
    do_sample = sample_random
    if problem in problem_samplers:
        do_sample = problem_samplers[problem]
    else:
        print(f"NOTE: no problem-specific sampler for {problem}, performing a naive random sample")

    # Sample examples
    sample_examples = None
    with open(sample_from, "r") as fp:
        sample_examples = [line.strip() for line in fp]

    # Auto-include examples
    include_all_examples = None
    with open(include_all, "r") as fp:
        include_all_examples = [line.strip() for line in fp]

    # Sample from examples
    examples = do_sample(
        sample_examples,
        include_all_examples,
        num_training,
        num_testing
    )

    # Name training / testing output files
    training_fname = "training.json" if output_prefix == None else f"{output_prefix}-training.json"
    testing_fname = "testing.json" if output_prefix == None else f"{output_prefix}-testing.json"

    # Write out training examples
    with open(training_fname, "w") as fp:
        for example in examples["training"]:
            fp.write(example + "\n")

    # Write out testing examples
    with open(testing_fname, "w") as fp:
        for example in examples["testing"]:
            fp.write(example + "\n")

    print(f"Training examples written to {training_fname}.")
    print(f"Testing examples written to {testing_fname}.")

if __name__ == "__main__":
    main()