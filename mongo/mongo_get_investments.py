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
    client = pymongo.MongoClient('mongodb+srv://cent:ArZrGZ9m3lQ4tYlW@centsible0.i6gri7x.mongodb.net/?retryWrites=true&w=majority')

    db = client.data

    collection = db['investments']

    test = collection.find_one({"ticker": "MSFT"})

    with open('db_output/investments.txt', 'w') as file:
        file.write(test["ticker"] + '\n')
        file.write(str(test["num_shares"]) + '\n')
        file.write(str(test["last_known_value"]) + '\n')
        file.write(str(test["last_total_value"]) + '\n')
        file.write(str(test["52_week_h"]) + '\n')
        file.write(str(test["52_week_l"]) + '\n')
        file.close()


if __name__ == '__main__':
    main()