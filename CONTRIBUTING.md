# Contributing to WAY

First off, thank you for considering contributing to WAY! It's people like you that make open source such a great community. We welcome any and all contributions, from bug reports to new features.

## How to Contribute

We strive to make contributing to WAY as easy and transparent as possible. Here are a few ways you can help:

-   **Reporting Bugs:** If you find a bug, please open an issue and provide as much detail as possible, including steps to reproduce the bug.
-   **Suggesting Enhancements:** If you have an idea for a new feature or an improvement to an existing one, please open an issue to discuss it.
-   **Submitting Pull Requests:** If you've fixed a bug or implemented a new feature, we'd love to see your work! Please submit a pull request with a clear description of your changes.

## Development Workflow

1.  **Fork the repository** on GitHub.
2.  **Clone your fork** to your local machine.
3.  **Create a new branch** for your changes:
    ```bash
    git checkout -b my-new-feature
    ```
4.  **Make your changes** and **add tests** for them.
5.  **Ensure all tests pass**:
    ```bash
    cd build
    make
    ./way_tests
    ```
6.  **Commit your changes** with a clear and descriptive commit message.
7.  **Push your changes** to your fork:
    ```bash
    git push origin my-new-feature
    ```
8.  **Open a pull request** on the main WAY repository.

## Code Style Guide

To maintain a consistent and readable codebase, we follow these style guidelines:

-   **C++ Standard:** We use C++17.
-   **Naming Conventions:**
    -   **Classes and Structs:** `PascalCase` (e.g., `AuthenticationService`)
    -   **Functions and Methods:** `camelCase` (e.g., `addStrategy`)
    -   **Variables:** `snake_case` (e.g., `auth_service`)
    -   **Namespaces:** `UPPERCASE` (e.g., `WAY`)
-   **Indentation:** 4 spaces.
-   **Braces:** Opening brace on the same line for classes, structs, and functions.

## Pull Request Guidelines

-   Please provide a clear and descriptive title and description for your pull request.
-   If your pull request addresses an existing issue, please link to it in the description.
-   Ensure that your code is well-tested and that all tests pass.
-   Follow the code style guide.

Thank you for your contributions!
