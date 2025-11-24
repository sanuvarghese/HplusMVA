import os
import ROOT

def merge_common_files(source_dirs, target_dir):
    """
    Merges ROOT files with the same names from two source directories into the target directory.

    Args:
        source_dirs (list): List containing exactly two source directories.
        target_dir (str): Directory to save the merged ROOT files.
    """
    if len(source_dirs) != 2:
        raise ValueError("Exactly two source directories must be provided.")

    # Ensure the target directory exists
    if not os.path.exists(target_dir):
        os.makedirs(target_dir)
        print(f"Created target directory: {target_dir}")

    # Get the list of files in each source directory
    files_in_dir1 = set(os.listdir(source_dirs[0]))
    files_in_dir2 = set(os.listdir(source_dirs[1]))

    # Find common files between the two directories
    common_files = files_in_dir1.intersection(files_in_dir2)
    common_base_files = [f for f in common_files if f.endswith("base.root")]

    print(f"Common files to be merged: {common_base_files}")

    # Merge the common files
    for base_name in common_base_files:
        input_file1 = os.path.join(source_dirs[0], base_name)
        input_file2 = os.path.join(source_dirs[1], base_name)
        output_file = os.path.join(target_dir, base_name)

        print(f"Merging {input_file1} and {input_file2} into {output_file}")

        # Merge using TFileMerger
        merger = ROOT.TFileMerger(False)  # False means no compression
        merger.AddFile(input_file1)
        merger.AddFile(input_file2)

        # Write the merged file to the target directory
        merger.OutputFile(output_file, "RECREATE")
        merger.Merge()

    print("Merging complete.")

if __name__ == "__main__":
    # Define source and target directories
    source_dirs = [
        "/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/pre/pre_res/",
        "/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/post/post_res/"
    ]
    target_dir = "/eos/cms/store/group/phys_b2g/savarghe/NewJEC/2018/pre_all/"

    # Run the merging process
    merge_common_files(source_dirs, target_dir)
