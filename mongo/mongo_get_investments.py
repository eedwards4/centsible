import pymongo
import os


def main():
    # Deal with file crap
    if not os.path.exists('db_output'):
        os.mkdir('db_output')

    try:
        os.remove('db_output/investments.txt')
        os.remove('db_output/investment_records.txt')
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
        url = credentials[2].strip()
        file.close()
    client = pymongo.MongoClient('mongodb+srv://{}:{}{}/?retryWrites=true&w=majority'.format(login, password, url))
    print("Connection successful. Retrieving data...")

    db = client.data
    chrono_db = client.chrono_data

    collection = db['investments']
    chrono_collection = chrono_db['investments']

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
        print("Data retrieved successfully.")

    print("Retrieving chrono data...")
    with open('db_output/investment_records.txt', 'w') as file:
        for obj in chrono_collection.find():
            file.write(str(obj["date"]) + '\n')
            file.write(obj["ticker"] + '\n')
            file.write(str(obj["num_shares"]) + '\n')
            file.write(str(obj["last_total_value"]) + '\n')
            file.write("END\n")
        file.close()
        print("Chrono data retrieved successfully.")


if __name__ == '__main__':
    main()