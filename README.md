# Polynomial Arithmetic Using Linked Lists

A backend project that performs polynomial addition, subtraction, and multiplication using a singly linked list in JavaScript with Node.js and Express.

## Features
- Polynomial representation using linked lists
- Addition of two polynomials
- Subtraction of two polynomials
- Multiplication of two polynomials
- Combining like terms
- Removing zero-coefficient terms
- Input validation and error handling
- REST API for polynomial calculations

## Technologies Used
- JavaScript
- Node.js
- Express.js
- npm
- Singly Linked Lists
- REST API

## Project Structure

```text
Arithmetic-Solution/
├── src/
│   ├── controllers/
│   ├── data-structures/
│   ├── routes/
│   ├── services/
│   └── server.js
├── test/
├── package.json
├── package-lock.json
├── .gitignore
└── README.md
```

## Installation

Clone the repository:

```bash
git clone https://github.com/pranavwagadre7987-a11y/Arithmetic-Solution.git
cd Arithmetic-Solution
npm install
```

## Run the Backend

```bash
npm run dev
```

Server URL: `http://localhost:3000`

## API Endpoints

### Health Check
`GET /api/health`

Checks whether the backend server is running.

### Polynomial Operations
`POST /api/polynomial/operation`

Supported operations:
- `add`
- `subtract`
- `multiply`

### Example Request

```json
{
  "operation": "add",
  "polynomialA": [
    { "coefficient": 3, "exponent": 2 },
    { "coefficient": 2, "exponent": 1 },
    { "coefficient": 1, "exponent": 0 }
  ],
  "polynomialB": [
    { "coefficient": 2, "exponent": 2 },
    { "coefficient": -2, "exponent": 1 },
    { "coefficient": 4, "exponent": 0 }
  ]
}
```

Expected result: `5x^2 + 5`

## Run Tests

```bash
npm test
```

## Data Structure

Each linked-list node contains:
- **Coefficient:** The numerical value of a term.
- **Exponent:** The power of the variable.
- **Next pointer:** Reference to the next node.

The linked list stores terms in descending order of exponents and combines terms with matching exponents.

## Learning Objectives
- Understand singly linked lists.
- Implement polynomial arithmetic algorithms.
- Develop a modular backend application.
- Build and test REST API endpoints.
- Handle invalid inputs and edge cases.

## Author
Pranav Wagadre
