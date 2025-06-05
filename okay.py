MAX_LINES = 3
MAX_BET=500
MIN_BET=1

def deposit():
    while True:
        amount=input("Please enter the Deposit Amount: $")
        if amount.isdigit():
            amount=int(amount)
            if amount>0:
                break
            else:
                print("Amount must be greater than $0.")
        else:
            print("Please enter a valid number for the amount")

    return amount

def get_lines():
    while True:
        lines = input("Please enter the number of lines you want to  bet on 1-3 : ")
        if lines.isdigit():
            lines = int(lines)
            if 0<lines<=3:
                break
            else:
                print("Lines must be greater than 0.")
        else:
            print("Please enter a valid number for valid number of lines")

    return lines

def get_bets(amount,lines):
    while True:
        betline = input("Please enter the BET Amount for each line: ")
        if betline.isdigit():
            bet = int(betline)*lines
            if MIN_BET<=bet<=int(amount) and MIN_BET<=bet<=MAX_BET:
                break
            elif bet>MAX_BET:
                print("BET must be smaller than $500")
            elif bet>int(amount):
                print(f"You have ${amount} in you wallet.")
            else:
                print("BET must be greater than $1")
        else:
            print("Please enter a valid BET Amount.")

    return bet

def main():
    balance=deposit()
    lines=get_lines()
    bet=get_bets(balance,lines)

    print(f'Your balance is ${balance} and you selected {lines} lines.You have successfully placed a bet of ${bet}')
    print(f"You have {balance} in you wallet.")


main()