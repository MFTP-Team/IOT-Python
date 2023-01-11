# This is a sample Python script.
import api
import sendUtil

# Press Maj+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

# Press the green button in the gutter to run the script.
def main():
    sendUtil.initUART()
    api.startAPI()

main()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
