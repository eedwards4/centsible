import pymongo
import os


def main():
    # Deal with file crap
    if not os.path.exists('db_output'):
        os.mkdir('db_output')

    try:
        os.remove('db_output/banks.txt')
        os.remove('db_output/bank_records.txt')
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

    collection = db['banks']
    chrono_collection = chrono_db['banks']

    # Access database and send the results to a file
    with open('db_output/banks.txt', 'w') as file:
        for obj in collection.find():
            file.write(obj["bname"] + '\n')
            file.write(str(obj["account_num"]) + '\n')
            file.write(obj["account_name"] + '\n')
            file.write(str(obj["balance"]) + '\n')
            file.write("END\n")
        file.close()
        print("Data retrieved successfully.")

    print("Retrieving chrono data...")
    with open('db_output/bank_records.txt', 'w') as file:
        for obj in chrono_collection.find():
            file.write(str(obj["date"]) + '\n')
            file.write(str(obj["account_num"]) + '\n')
            file.write(str(obj["balance"]) + '\n')
            file.write("END\n")
        file.close()
        print("Chrono data retrieved successfully.")


if __name__ == '__main__':
    main()
