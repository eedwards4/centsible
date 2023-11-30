import pymongo
import os

# mongo user: cent
# mongo password: ArZrGZ9m3lQ4tYlW


def main():
    # Deal with file crap
    if not os.path.exists('db_output'):
        os.mkdir('db_output')

    try:
        os.remove('db_output/banks.txt')
    except OSError:
        pass

    # End file crap

    # Connect to the database
    print("Attempting to connect to the database...")
    client = pymongo.MongoClient('mongodb+srv://cent:ArZrGZ9m3lQ4tYlW@centsible0.i6gri7x.mongodb.net/?retryWrites=true&w=majority')

    db = client.data

    collection = db['banks']

    test = collection.find_one({"account_num": "98709870987"})
    # Access database and send the results to a file
    with open('db_output/banks.txt', 'w') as file:
        file.write(test["bname"] + '\n')
        file.write(test["account_num"] + '\n')
        file.write(test["account_name"] + '\n')
        file.write(test["balance"] + '\n')
        file.close()


if __name__ == '__main__':
    main()
