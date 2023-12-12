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

    collection = db['investments']
    chrono_collection = chrono_db['investments']

    with open('db_input/investments.txt', 'r') as file:
        # Get the data from the file and send it to the database. If the record already exists, update it.
        while True:
            ticker = file.readline().strip()
            if ticker == '':
                break
            num_shares = int(file.readline().strip())
            last_known_value = float(file.readline().strip())
            last_total_value = float(file.readline().strip())
            fifty_two_week_high = float(file.readline().strip())
            fifty_two_week_low = float(file.readline().strip())
            file.readline() # Skip the END line
            if collection.count_documents({'ticker': ticker}) == 0:
                collection.insert_one({'ticker': ticker, 'num_shares': num_shares, 'last_known_value': last_known_value,
                                       'last_total_value': last_total_value, '52_week_h': fifty_two_week_high,
                                       '52_week_l': fifty_two_week_low})
            else:
                collection.update_one({'ticker': ticker}, {'$set': {'num_shares': num_shares,
                                                                    'last_known_value': last_known_value,
                                                                    'last_total_value': last_total_value,
                                                                    '52_week_h': fifty_two_week_high,
                                                                    '52_week_l': fifty_two_week_low}})
        file.close()
        print("Data sent successfully.")

    print("Sending chrono data...")
    with open("db_input/investment_records.txt", 'r') as file:
        # For each record in the file, check if it's date already exists in the database. If it does not, add it.
        while True:
            date = file.readline().strip()
            if date == '':
                break
            ticker = file.readline().strip()
            num_shares = int(file.readline().strip())
            last_total_value = float(file.readline().strip())
            file.readline()  # Skip the END line
            if chrono_collection.count_documents({'date': date, 'ticker': ticker}) == 0:
                chrono_collection.insert_one({'date': date, 'ticker': ticker, 'num_shares': num_shares,
                                              'last_total_value': last_total_value})
        file.close()
        print("Chrono data sent successfully.")


if __name__ == '__main__':
    main()

