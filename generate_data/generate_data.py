import random
from datetime import datetime

""" ENTER THE CONFIG INFO BELOW """

# input file path
_INPUT_FILE_PATH_ = './in.txt'

# output file path (trailing slash required)
_OUTPUT_FILE_PATH_ = './'

# what's the max variance student submissions should have?
_FUZZ_FACTOR_ = 0.0333

# How many output files do you want?
_NUM_OUTPUTS_ = 10

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
    images = read_images(_INPUT_FILE_PATH_)

    for i in range(1, _NUM_OUTPUTS_ + 1):
        write_submission('{}out{:03d}.txt'.format(_OUTPUT_FILE_PATH_, i), images, 0.333, datetime.now())


def read_images(file_path):
    in_file = open(file_path)
    in_lines = in_file.readlines()

    rectangle_header = 'rect:'
    header_len = len(rectangle_header)

    image = None
    images = []

    for line in in_lines:
        if line[:header_len] == rectangle_header:
            rect_spec_split = line[header_len:].split()
            rectangle = Rectangle(int(rect_spec_split[0]), int(rect_spec_split[1]),
                                  int(rect_spec_split[2]), int(rect_spec_split[3]),
                                  ' '.join(rect_spec_split[4:]))

            if image:
                image.rectangles.append(rectangle)

        else:
            image_spec_split = line.split()
            dim_split = image_spec_split[1].split('x')

            if image:
                images.append(image)

            image = Image(image_spec_split[0], int(dim_split[0]), int(dim_split[1]))

    in_file.close()
    return images


def write_submission(file_path, images, fuzz_factor, seed):
    random.seed(seed)
    out_file = open(file_path, 'w')

    for img in images:
        out_file.write(str(img) + '\n')
        rectangles_copy = img.rectangles[:]
        random.shuffle(rectangles_copy)

        for rect in rectangles_copy:
            fuzzed = 'rect:{:d} {:d} {:d} {:d} {}\n'.format(
                rect.x1 + int(rect.x1 * random.uniform(-fuzz_factor, fuzz_factor)),
                rect.y1 + int(rect.y1 * random.uniform(-fuzz_factor, fuzz_factor)),
                rect.x2 + int(rect.x2 * random.uniform(-fuzz_factor, fuzz_factor)),
                rect.y2 + int(rect.y2 * random.uniform(-fuzz_factor, fuzz_factor)),
                rect.tag
            )
            out_file.write(fuzzed)

    out_file.close()


if __name__ == '__main__':
    main()
