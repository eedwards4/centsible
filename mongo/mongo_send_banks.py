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
    print("Connection successful. Sending data...")

    db = client.data
    chrono_db = client.chrono_data

    collection = db['banks']
    chrono_collection = chrono_db['banks']

    with open('db_input/banks.txt', 'r') as file:
        # Get the data from the file and send it to the database. If the record already exists, update it.
        while True:
            bname = file.readline().strip()
            account_num = file.readline().strip()
            if account_num == '':
                break
            account_name = file.readline().strip()
            balance = float(file.readline().strip())
            file.readline() # Skip the END line
            if collection.count_documents({'account_num': account_num}) == 0:
                collection.insert_one({'bname': bname, 'account_num': account_num, 'account_name': account_name,
                                       'balance': balance})
            else:
                collection.update_one({'account_num': account_num}, {'$set': {'bname': bname,
                                                                    'account_name': account_name,
                                                                    'balance': balance}})
        file.close()
        print("Data sent successfully.")

#    TODO: FIX WHATEVER IS WRONG WITH THIS
#    print("Sending chrono data...")
#    with open('db_input/bank_records.txt', 'r') as file:
#        # For each record in the file, check if it's date already exists in the database. If it does not, add it.
#        while True:
#            date = file.readline().strip()
#            if date == '':
#                break
#            account_num = file.readline().strip()
#            balance = float(file.readline().strip())
#            file.readline()  # Skip the END line
#            if chrono_collection.count_documents({'date': date, 'account_num': account_num}) == 0:
#                chrono_collection.insert_one({'date': date, 'account_num': account_num, 'balance': balance})
#        file.close()
#        print("Chrono data sent successfully.")


if __name__ == '__main__':
    main()

