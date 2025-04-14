# ✨ Contributing to eaC - Executable ASCII Canvas

First off, thank you for considering contributing to eaC! We appreciate your interest and are excited to welcome you to our community. ❤️

This document will guide you through the contribution process, ensuring a smooth and productive experience for everyone.

## Table of Contents

* [Code of Conduct](#code-of-conduct)
* [Ways to Contribute](#ways-to-contribute)
* [Getting Started](#getting-started)
    * [Setting up Your Environment](#setting-up-your-environment)
    * [Project Structure](#project-structure)
* [Contributing Code](#contributing-code)
    * [Finding an Issue](#finding-an-issue)
    * [Creating a Pull Request](#creating-a-pull-request)
    * [Coding Guidelines](#coding-guidelines)
    * [Testing](#testing)
* [Reporting Bugs](#reporting-bugs)
* [Suggesting Enhancements](#suggesting-enhancements)
* [Community](#community)
* [License](#license)

## Code of Conduct

Please review our [Code of Conduct](CODE_OF_CONDUCT.md) to understand the expectations for behavior in our community. We are committed to creating a welcoming and inclusive environment for everyone.

## Ways to Contribute

There are many ways to contribute to eaC, beyond just writing code:

* **Reporting Bugs:** Help us identify and fix issues by providing detailed bug reports.
* **Suggesting Enhancements:** Propose new features or improvements to existing functionality.
* **Improving Documentation:** Make our documentation clearer, more concise, or more helpful (including this `CONTRIBUTING.md`!).
* **Testing:** Help us ensure the quality of eaC by testing new features and bug fixes.
* **Code Contributions:** Implement new features, fix bugs, or improve the efficiency of the code.

## Getting Started

### Setting up Your Environment

1.  **Obtain the Source Code:**
    * **Clone the repository:** `git clone https://github.com/devnihal/eaC.git`
    * **Navigate to the project directory:** `cd eaC`
2.  **Install Dependencies:**
    * Ensure you have `gcc` (or a compatible C compiler) and `make` installed.
3.  **Build the Project:**
    * Run `make` to compile the code. This will create the executable in the `builds/` directory. Alternatively, you can use the manual compilation commands mentioned in the [Usage](#️-usage) section of the `README.md`.

### Project Structure

Familiarize yourself with the project's file structure:

```
eaC/
├── src/            # Source code (main.c, canvas.c, canvas.h)
├── builds/         # Compiled executable
├── drawings/       # Example drawing files
├── .gitignore      # Files to ignore in Git
├── README.md       # Project documentation
├── LICENSE         # MIT License
└── CONTRIBUTING.md # Contribution guidelines
```

## Contributing Code

### Finding an Issue

* Check the [issue tracker](https://github.com/devnihal/eaC/issues) for open issues.
* Look for issues labeled "good first issue" if you're new to contributing.
* If you want to work on an issue, please comment on it to let others know.

### Creating a Pull Request

1.  **Fork the repository.**
2.  **Create a new branch** for your changes: `git checkout -b feature/your-feature-name`
3.  **Make your changes.**
4.  **Test your changes** (see [Testing](#testing)).
5.  **Commit your changes:** `git commit -m "Add your descriptive commit message"`
6.  **Push to your fork:** `git push origin feature/your-feature-name`
7.  **Create a pull request** on GitHub, targeting the `main` branch.
8.  **Be responsive to feedback** from reviewers.

### Coding Guidelines

* Follow the existing coding style for consistency.
* Write clear and concise C code with meaningful variable and function names.
* Comment your code where necessary to explain complex logic.
* Keep functions relatively short and focused on a single task.
* Avoid global variables where possible.
* Format your code using a consistent indentation style (e.g., 4 spaces or tabs).
* Adhere to standard C practices.

### Testing

* Ensure your changes compile cleanly without warnings or errors.
* Test the specific functionality you've added or modified by running the `eac` executable and using the relevant commands.
* If you've fixed a bug, try to reproduce the original bug with your changes to confirm the fix.
* For new features, consider how they interact with existing commands.

## Reporting Bugs

If you find a bug, please create a new issue on GitHub. Include the following information:

* **Clear and descriptive title.**
* **Steps to reproduce the bug.**
* **Expected behavior.**
* **Actual behavior.**
* **Any relevant error messages or output from the `eac` program.**
* **Your operating system and terminal environment.**

## Suggesting Enhancements

If you have an idea for a new feature or an improvement, please create a new issue on GitHub. Include the following information:

* **Clear and descriptive title.**
* **Detailed description of the proposed enhancement.**
* **Use cases and benefits of the enhancement.**
* **Any potential implementation ideas or challenges (if you have them).**

## Community

We encourage you to engage with the eaC community. You can:

* Participate in discussions on GitHub issues and pull requests.
* Share your creations and scripts using eaC.
* Help others by answering questions or providing assistance.

## License

By contributing to eaC, you agree that your contributions will be licensed under the [MIT License](./LICENSE.txt).

---

Thank you again for your interest in contributing to eaC! We look forward to your contributions. 😊