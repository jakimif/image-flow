# ImageFlow

ImageFlow is a command-line tool designed to help you perform batch operations on your photo files. Whether you need to rename, convert, resize, or scale your images, ImageFlow has got you covered. This README.md file will guide you through the various modes and options available in ImageFlow.

## Modes

ImageFlow offers four operating modes, and only one mode can be active at a time. You can activate a mode by choosing one of the following flags:

- `--rename`: Enable file rename mode
- `--convert`: Enable file conversion mode
- `--resize`: Enable file resize mode
- `--scale`: Enable file scaling mode

## Common Options

The following options are common to all modes:

- `--folder`: Specifies the folder where ImageFlow will work
- `--filter`: Specifies the filter used to select files

Now, let's dive into each mode and explore their specific options.

### Rename Mode

In Rename mode, each selected file will be renamed to the format `<prefix>_<n>.<ext>`, where `<prefix>` and `<n>` can be specified via options. `<ext>` represents the original file extension and remains unchanged.

Options for Rename mode:

- `--prefix=<prefix>`: Prefix used when renaming files
- `--start=<n>`: Start number to add to each renamed file

### Convert Mode

In Convert mode, each selected file will be converted from the `<from>` format to the `<to>` format. The source and target extensions cannot be the same, and the file name remains unchanged.

Options for Convert mode:

- `--from=<jpg|png|tga>`: Source extension for conversion
- `--to=<jpg|png|tga>`: Target extension for conversion

### Resize Mode

In Resize mode, each selected file will be resized to the specified dimensions using the following options. Note that `N` must be greater than or equal to 1.

Options for Resize mode:

- `--width=<n>`: New image width
- `--height=<n>`: New image height

### Scale Mode

In Scale mode, each selected file will be uniformly scaled by the factor specified in the following option. Note that `N` must be greater than 0 and will be interpreted as a floating-point number.

Options for Scale mode:

- `--amount=<n>`: Scale factor to apply to each selected image

## Usage Examples

Here are some examples to demonstrate how you can use ImageFlow for different operations:

1. Rename all files in the folder `/Users/username/Documents/images` with the extension `.png` to `travel_n.png`, where `N` starts from 0:

```shell
ImageFlow --rename --folder="/Users/username/Documents/images" --filter=".png" --prefix="travel_" --start=0
```

2. Resize all files in the folder `/Users/username/Documents/images` with the extension `.jpg` to a size of 500x500:

```shell
ImageFlow --resize --folder="/Users/username/Documents/images" --filter=".jpg" --width=500 --height=500
```

3. Convert all files in the folder `/Users/username/Documents/images` from `png` to `jpg`:

```shell
ImageFlow --convert --folder="/Users/username/Documents/images" --from=png --to=jpg
```

4. Reduce the size of all `png` files in the folder `/Users/username/Documents/images` by half:

```shell
ImageFlow --scale --folder="/Users/username/Documents/images" --filter=".png" --amount=0.5
```

Certainly! Here are the compilation instructions in English for your README.md:

## Compilation

Follow the steps below to compile the project:

1. Make sure you have CMake installed on your machine. You can check if CMake is installed by running the following command in the terminal:

   ```shell
   cmake --version
   ```

   If CMake is installed, you will see the CMake version being displayed. Otherwise, install CMake before proceeding.

2. Navigate to the root directory of the project in your terminal.

3. Create a separate build directory (recommended) to store the build files. Execute the following commands in the terminal:

   ```shell
   mkdir build
   cd build
   ```

4. Inside the build directory, run the CMake command to configure the build environment:

   ```shell
   cmake ..
   ```

5. After the previous step completes, you can proceed with the compilation process. Execute the following command:

   ```shell
   make
   ```

6. Now, the project will be compiled. You will find the executable named "ImageFlow" in the build directory.

   ```shell
   ./ImageFlow
   ```
