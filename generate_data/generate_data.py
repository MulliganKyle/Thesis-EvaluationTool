import random
from datetime import datetime

""" ENTER THE CONFIG INFO BELOW """

# input file names
_INPUT_FILE_NAMES_ = [
    'Output_EZRA1-clean.txt',
    'Output_EZRA2-clean.txt',
    'OutputANA-clean.txt',
    'OutputErika-clean.txt',
    'OutputJohn-clean.txt'
]

# directory containing input files (trailing slash required)
_INPUT_FILE_DIR_ = '../expertFiles/'

# output file path (trailing slash required)
_OUTPUT_FILE_PATH_ = '../expertFiles/'

# what's the max variance student submissions should have?
_FUZZ_FACTOR_ = 0 #0.0333

# How many output files do you want?
_NUM_OUTPUTS_ = 1

# Shuffle the output list?
_SHUFFLE_ON_ = False

"""""""""""""""""""""CONFIG END"""


class Image():
    def __init__(self, name, x, y):
        self.name = name
        self.x_dim = x
        self.y_dim = y
        self.rectangles = []

    def __str__(self):
        return '{} {:d}x{:d}'.format(self.name, self.x_dim, self.y_dim)


class Rectangle():
    def __init__(self, x1, y1, x2, y2, tag):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.tag = tag


def main():
    counter = 0
    tag_dict = {}

    for in_file_ndx, in_file_name in enumerate(_INPUT_FILE_NAMES_, start=1):
        input_file_path  = _INPUT_FILE_DIR_ + in_file_name
        images, counter = read_images(input_file_path, tag_dict, counter)

        for output_ndx in range(1, _NUM_OUTPUTS_ + 1):
            out_file_name = '{}out_{:03d}_{:03d}_{}'.format(
                _OUTPUT_FILE_PATH_, 
                in_file_ndx, 
                output_ndx, 
                in_file_name
            )
            write_submission(out_file_name, images, 0.333, datetime.now())


def read_images(file_path, tag_dict, counter):
    in_file = open(file_path)
    in_lines = in_file.readlines()

    rectangle_header = 'rect:'
    header_len = len(rectangle_header)

    image = None
    images = []

    for line in in_lines:
        if line[:header_len] == rectangle_header:
            rect_spec_split = line[header_len:].split()
            tag_str = ' '.join(rect_spec_split[4:])

            if tag_str in tag_dict:
                val = tag_dict[tag_str]
            else:
                counter += 1
                val = counter
                tag_dict[tag_str] = counter


            rectangle = Rectangle(int(rect_spec_split[0]), int(rect_spec_split[1]),
                                  int(rect_spec_split[2]), int(rect_spec_split[3]),
                                  val)

            if image:
                image.rectangles.append(rectangle)

        else:
            image_spec_split = line.split()
            dim_split = ['0', '0'] # image_spec_split[1].split('x')

            if image:
                images.append(image)

            image = Image(image_spec_split[0], int(dim_split[0]), int(dim_split[1]))

    in_file.close()
    return images, counter


def write_submission(file_path, images, fuzz_factor, seed):
    random.seed(seed)
    out_file = open(file_path, 'w')

    for img in images:
        out_file.write(str(img) + '\n')
        rectangles_copy = img.rectangles[:]

        if _SHUFFLE_ON_:
            random.shuffle(rectangles_copy)

        for rect in rectangles_copy:
            fuzzed = 'rect:{:d} {:d} {:d} {:d} {:d}\n'.format(
                rect.x1 + int(rect.x1 * random.uniform(-fuzz_factor, fuzz_factor) if _FUZZ_FACTOR_ else 0),
                rect.y1 + int(rect.y1 * random.uniform(-fuzz_factor, fuzz_factor) if _FUZZ_FACTOR_ else 0),
                rect.x2 + int(rect.x2 * random.uniform(-fuzz_factor, fuzz_factor) if _FUZZ_FACTOR_ else 0),
                rect.y2 + int(rect.y2 * random.uniform(-fuzz_factor, fuzz_factor) if _FUZZ_FACTOR_ else 0),
                rect.tag
            )
            out_file.write(fuzzed)

    out_file.close()


if __name__ == '__main__':
    main()
