import pymongo
import os


def main():
    # Deal with file crap
    if not os.path.exists('db_output'):
        os.mkdir('db_output')

    try:
        os.remove('db_output/banks.txt')
    except OSError:
        pass

    with open('db_output/banks.txt', 'w') as file:
        file.write('Banks!\n')  # TEMP

    # End file crap


if __name__ == '__main__':
    main()
