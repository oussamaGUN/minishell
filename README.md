# Minishell

Welcome to Minishell, a lightweight Unix shell implementation written in C. This project aims to provide a simplified command-line interface with basic shell functionalities.

## Features

- Command execution: Run various commands and programs.
- Input/output redirection: Redirect input and output streams.
- Pipelines: Connect multiple commands using pipes.
- Environment variables: Manage and manipulate environment variables.
- Signal handling: Handle signals like Ctrl+C and Ctrl+Z.
- Built-in commands: Includes commonly used commands like `cd`, `echo`, and `exit`.

## Getting Started

To get started with Minishell, follow these steps:

1. Clone the repository: `git clone https://github.com/BL4KCY/minishell.git`
2. Navigate to the project directory: `cd minishell`
3. Build the project: `make`
4. Run Minishell: `./minishell`

## Usage

Once you have Minishell up and running, you can start using it as a command-line interface. Here are some examples of how to use the shell:

- Execute a command: `ls -l`
- Redirect input: `cat < input.txt`
- Redirect output: `ls > output.txt`
- Create a pipeline: `ls | grep "example"`
- Set an environment variable: `export MY_VAR=Hello`
- Access an environment variable: `echo $MY_VAR`
- Change directory: `cd /path/to/directory`
- Exit Minishell: `exit`

For more detailed information on how to use Minishell and its features, please refer to the [documentation](https://github.com/BL4KCY/minishell/wiki).

## Contributing

Contributions are welcome! If you would like to contribute to Minishell, please follow the guidelines outlined in the [CONTRIBUTING.md](https://github.com/BL4KCY/minishell/blob/master/CONTRIBUTING.md) file.

## License

Minishell is licensed under the [MIT License](https://github.com/BL4KCY/minishell/blob/master/LICENSE).
