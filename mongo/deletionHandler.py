import pymongo
import os


def main():
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
    print("Connection successful. Handling deletions...")

    db = client.data

    banks = db['banks']
    investments = db['investments']

    with open("db_input/deletions.txt", 'r') as file:
        # Get each line of the file and delete the corresponding record from the databases.
        while True:
            line = file.readline().strip()
            if line == '':
                break
            if banks.find_one({'account_num': line}) is not None:
                banks.delete_one({'account_num': line})
            elif investments.find_one({'ticker': line}) is not None:
                investments.delete_one({'ticker': line})
        file.close()
        if os.path.exists("db_input/deletions.txt"):  # It better exist...
            os.remove("db_input/deletions.txt")
        print("Deletions handled successfully.")



if __name__ == '__main__':
    main()