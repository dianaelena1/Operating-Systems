import multiprocessing
import string

def count_letter(text, char, results_dict):
    count = text.lower().count(char)
    results_dict[char] = count

def main():
    print("Enter text: ")
    sample_text = input(">")

    manager = multiprocessing.Manager()
    results = manager.dict()
    processes = []
    for letter in string.ascii_lowercase:
        p = multiprocessing.Process(target=count_letter, args=(sample_text, letter, results))
        processes.append(p)
        p.start()

    for p in processes:
        p.join()

    print(f"{'Letter':<8} | {'Frequency':<10}")
    print("-" * 20)

    for letter in sorted(results.keys()):
        if results[letter] >0:
            print(f"{letter.upper():<8} | {results[letter]:<10}")

if __name__ == "__main__":
    main()