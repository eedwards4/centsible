import pymongo
import os


def main():
    # Deal with file crap
    if not os.path.exists('db_output'):
        os.mkdir('db_output')

    try:
        os.remove('db_output/investments.txt')
    except OSError:
        pass

    # End file crap

    # Connect to the database
    print("Attempting to connect to the database...")
    # Get mongo login
    with open('mongo_login.txt', 'r') as file:
        credentials = file.readlines()
        login = credentials[0].strip()
        password = credentials[1].strip()
        file.close()
    client = pymongo.MongoClient('mongodb+srv://{}:{}@centsible0.i6gri7x.mongodb.net/?retryWrites=true&w=majority'.format(login, password))

    db = client.data

    collection = db['investments']

    # Access database and send the results to a file
    with open('db_output/investments.txt', 'w') as file:
        for obj in collection.find():
            file.write(obj["ticker"] + '\n')
            file.write(str(obj["num_shares"]) + '\n')
            file.write(str(obj["last_known_value"]) + '\n')
            file.write(str(obj["last_total_value"]) + '\n')
            file.write(str(obj["52_week_h"]) + '\n')
            file.write(str(obj["52_week_l"]) + '\n')
            file.write("END\n")
        file.close()


if __name__ == '__main__':
    main()