# API Rate Limiter (Node.js + C++ Addon)

This project implements a high-performance API rate limiting system using C++ and exposes its functionality to a Node.js application through a native addon built with Node-API and CMake. The goal is to combine the performance of C++ with the accessibility of JavaScript, enabling scalable and efficient API request management.

## Features

- Built using C++ for optimized performance in critical operations
- Exposed to Node.js via Node-API using the `node-addon-api` library
- Supports four widely-used rate limiting algorithms:
  - Fixed Window
  - Sliding Log
  - Token Bucket
  - Leaky Bucket
- TypeScript-based Express server for integration and testing


## Prerequisites

- Node.js (version 18 or later recommended)
- CMake (version 3.15 or later)
- Python (used by node-gyp and cmake-js)
- C++ compiler (Visual Studio on Windows, or GCC/Clang on Unix)
- TypeScript: `npm install -g typescript`
- cmake-js: `npm install -g cmake-js`

## Local Installation:
- clone the repo:
    - `git clone https://github.com/divyansh12git/api_rate_limiter.git`

- cd into folder
- install dependencies:
    - `npm i `
- Compile the C++ source using CMake and cmake-js:
    - `npm run build`
- Start the server:
    - `npm run serve`

## API structure
- GET `/limiter/fixed?name=<user_id>` – Checks using the Fixed Window rate limiter

- GET `/limiter/sliding?name=<user_id>` – Checks using the Sliding Log rate limiter

- GET `/limiter/token?name=<user_id>` – Checks using the Token Bucket rate limiter

- GET `/limiter/leaky?name=<user_id>` – Checks using the Leaky Bucket rate limiter

- Response Format:
`
{
  "activity": true,
  "answer": "user allowed"
}`

 ## Author
Developed by Divyansh Gupta
- This project was driven by the curiosity to combine the performance and speed of C++ with the flexibility of a mature web framework Node.js.
