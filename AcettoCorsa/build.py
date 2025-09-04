import os
import shutil
import subprocess

project_dir = os.path.abspath(os.path.dirname(__file__))
source_dir = os.path.join(project_dir, ".")
build_dir_x86 = os.path.join(project_dir, "build/build_x86")
build_dir_x64 = os.path.join(project_dir, "build/build_x64")
out_dir = os.path.join(project_dir, "build/out")

def run_cmake(build_dir, arch):
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)
    generator = "Visual Studio 17 2022"
    platform = "Win32" if arch == "x86" else "x64"
    cmake_cmd = [
        "cmake",
        "-S", source_dir,
        "-B", build_dir,
        "-G", generator,
        "-A", platform,
        f"-DLIB_TYPE=SHARED"
    ]
    print(f"Configuring {arch}...")
    subprocess.run(cmake_cmd, check=True)
    print(f"Building {arch}...")
    subprocess.run(["cmake", "--build", build_dir, "--config", "Release"], check=True)

def copy_outputs():
    # Copy all files from x64 Release
    release_dir_x64 = os.path.join(build_dir_x64, "Release")
    if os.path.exists(release_dir_x64):
        if not os.path.exists(out_dir):
            os.makedirs(out_dir)
        for filename in os.listdir(release_dir_x64):
            src_file = os.path.join(release_dir_x64, filename)
            dst_file = os.path.join(out_dir, filename)
            if os.path.isfile(src_file):
                shutil.copy2(src_file, dst_file)
                print(f"Copied x64: {src_file} -> {dst_file}")
    else:
        print(f"x64 Release directory not found: {release_dir_x64}")

    # Copy only .lib file from x86 Release
    release_dir_x86 = os.path.join(build_dir_x86, "Release")
    if os.path.exists(release_dir_x86):
        for filename in os.listdir(release_dir_x86):
            if filename.lower().endswith(".lib"):
                src_file = os.path.join(release_dir_x86, filename)
                dst_file = os.path.join(out_dir, filename)
                if os.path.isfile(src_file):
                    shutil.copy2(src_file, dst_file)
                    print(f"Copied x86 .lib: {src_file} -> {dst_file}")
    else:
        print(f"x86 Release directory not found: {release_dir_x86}")

if __name__ == "__main__":
    run_cmake(build_dir_x86, "x86")
    run_cmake(build_dir_x64, "x64")
    copy_outputs()
    print("Builds completed for x86 and x64. Outputs copied to build/out.")