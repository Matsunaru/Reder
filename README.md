# Image File Processor

This is a console program for processing image files in formats PPM, PGM, and PBM.

## Usage

1. Run the program.
2. When prompted, enter the name of the image file you want to process.
3. The program will display the following information about the image:
    - Width and height of the image
    - Most frequently occurring color and its occurrences
    - Number of unique colors
4. After processing, the program will ask if you want to load another file. Enter "yes" to load another file or "no" to end the program.

## How to Run

1. Clone the repository.
2. Compile the source code using a C++ compiler.
3. Run the compiled executable.

## Example
Enter the file name: example.ppm

File format: P3
Image width: 200
Image height: 500
Number of unique colors: 500 colors
Color details:
255 255 255 - 100
0 0 0 - 200
...
Maximum color value: 255

Do you want to load another file (yes/no):

## File Formats Supported

- P1: Portable Bitmap (ASCII)
- P2: Portable Graymap (ASCII)
- P3: Portable Pixmap (ASCII)
- P4: Portable Bitmap (Binary)//Binary will open but it will display only besic information
- P5: Portable Graymap (Binary)
- P6: Portable Pixmap (Binary)

## Note

If the file format is not recognized or the file cannot be opened, the program will display an error message and exit.

## License

This project is licensed under the (public copyright license).