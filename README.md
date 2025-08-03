# WAY (Who Are You) - A Modern C++ Authentication Framework

**WAY** is a flexible and extensible authentication framework for C++, designed to support a variety of popular authentication strategies. It provides a clean, modern, and easy-to-use API for developers to secure their applications.

## Philosophy

WAY is built with a focus on modularity and extensibility. The core of the framework is the `IAuthenticationStrategy` interface, which allows for the seamless integration of new authentication methods. This design ensures that WAY can adapt to the evolving landscape of authentication technologies.

## Features

- **Multiple Authentication Strategies:** Out-of-the-box support for:
    - **Username/Password:** A classic and straightforward authentication method.
    - **JSON Web Tokens (JWT):** A modern, stateless authentication mechanism.
    - **OAuth 2.0:** Support for third-party authentication providers, with Google as the first implementation.
- **Extensible Design:** The `IAuthenticationStrategy` interface makes it easy to add new authentication methods.
- **Modern C++:** Built with C++17, leveraging modern language features for a clean and efficient codebase.
- **CMake Build System:** A professional and scalable build system that simplifies compilation and dependency management.
- **Unit Tested:** A comprehensive test suite to ensure the reliability and correctness of the framework.

## Architecture

The framework is composed of three main components:

1.  **`IAuthenticationStrategy`:** An interface that defines the contract for all authentication methods. Each strategy must implement the `authenticate` method.
2.  **Concrete Strategies:** Implementations of the `IAuthenticationStrategy` interface, such as `PasswordStrategy`, `JwtStrategy`, and `GoogleOAuth2Strategy`.
3.  **`AuthenticationService`:** A service that manages the available authentication strategies and provides a single entry point for the server.

## Getting Started

### Prerequisites

- A C++17 compatible compiler (e.g., GCC, Clang, MSVC)
- CMake 3.10 or later
- Git

### Building the Project

1.  Clone the repository:

    ```bash
    git clone https://github.com/your-username/WAY.git
    cd WAY
    ```

2.  Initialize the submodules:

    ```bash
    git submodule update --init --recursive
    ```

3.  Create a build directory:

    ```bash
    mkdir build
    cd build
    ```

4.  Configure the project with CMake:

    ```bash
    cmake ..
    ```

5.  Build the project:

    ```bash
    make
    ```

### Running the Server

The server will start on port 8080. You can use `curl` to send authentication requests.

```bash
./way_server
```

### Running the Tests

```bash
./way_tests
```

## Usage

The server exposes a single endpoint, `/authenticate`, which accepts POST requests. The request body must be a JSON object with the following format:

```json
{
  "strategy": "<strategy_name>",
  "credentials": {
    "<credential_key>": "<credential_value>",
    ...
  }
}
```

### Example: Password Authentication

```bash
curl -X POST -H "Content-Type: application/json" -d '{
  "strategy": "password",
  "credentials": {
    "username": "testuser",
    "password": "password123"
  }
}' http://localhost:8080/authenticate
```

### Example: JWT Authentication

First, you need to generate a JWT token. Then, you can use it to authenticate.

```bash
# This is a placeholder for a real token
TOKEN="your.jwt.token"

curl -X POST -H "Content-Type: application/json" -d "{
  \"strategy\": \"jwt\",
  \"credentials\": {
    \"token\": \"$TOKEN\"
  }
}" http://localhost:8080/authenticate
```

## Roadmap

Here are some of the features and improvements planned for the future of WAY:

-   **Database Integration:**
    -   [ ] **User Storage:** Implement database connectors (e.g., SQLite) to store and manage user credentials securely, replacing the current in-memory user list. (Note: PostgreSQL, MySQL, and MongoDB integration will likely require a C++ package manager like vcpkg or Conan for dependency management.)
    -   [ ] **Session Management:** Introduce session management capabilities with support for backend stores like Redis to manage user sessions effectively.

-   **Enhanced Security:**
    -   [ ] **Password Hashing:** Integrate a robust password hashing library (e.g., Argon2, bcrypt) to securely store user passwords.
    -   [ ] **Rate Limiting:** Implement rate limiting to protect against brute-force attacks.

-   **Improved Developer Experience:**
    -   [ ] **Command-Line Interface (CLI):** Develop a CLI tool to manage the server, including starting/stopping the server and managing configuration through environment variables.
    -   [ ] **Configuration Management:** Implement a more robust configuration system to manage secrets and other settings.

-   **Expanded Authentication Strategies:**
    -   [ ] **OpenID Connect:** Add support for OpenID Connect, building on the existing OAuth 2.0 implementation.
    -   [ ] **Other OAuth Providers:** Add support for other popular OAuth providers like GitHub, Facebook, and Twitter.

## Contributing

Contributions are welcome! Please see our [Contributing Guidelines](CONTRIBUTING.md) for more information.

## License

This project is licensed under the terms of the **GNU General Public License v3.0**.
