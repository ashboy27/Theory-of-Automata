# Theory of Automata Project: Regular Expression Based Text Analyzer

Welcome to the **Theory of Automata Project** repository! This project is a comprehensive Regular Expression Based Text Analyzer that includes features like spell check, word recommendation, and auto-correct. The project leverages a Trie data structure for efficient word storage and search, and employs dynamic programming techniques to find close matches to user-input words. Additionally, the project features a graphical user interface (GUI) built using SFML (Simple and Fast Multimedia Library).

## Features

- **Spell Check**: Identifies and highlights misspelled words in the input text.
- **Word Recommendation**: Suggests possible corrections for misspelled words.
- **Auto-Correct**: Automatically corrects misspelled words based on the closest matches.
- **Efficient Word Storage and Search**: Utilizes a Trie data structure for fast and efficient word operations.
- **Dynamic Programming**: Applies dynamic programming concepts to find words that are close to the input word, enhancing the recommendation and auto-correct features.
- **Graphical User Interface**: Implements a user-friendly GUI using SFML for an interactive user experience.

## Installation

To get started with this project, follow these steps:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/theory-of-automata-project.git
    cd theory-of-automata-project
    ```

2. **Install dependencies**:
    Ensure you have SFML installed on your system. You can follow the instructions on the [SFML website](https://www.sfml-dev.org/download.php) to install it.

3. **Build the project**:
    - If using a Makefile:
        ```bash
        make
        ```
    - If using a different build system, follow the respective instructions to compile the code.

## Usage

After building the project, you can run the text analyzer:

```bash
./main
