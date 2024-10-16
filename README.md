# Operating Systems Lab Solutions

This repository contains solutions to various laboratory exercises for the **Operating Systems** course. Each lab demonstrates key concepts in operating systems, including process management, synchronization, inter-process communication, and more.

## Table of Contents

- [Lab 1 - Makefile](./lab1)
- [Lab 2 - Libraries](#lab2)
- [Lab 3 - Files](#lab3)
- [Lab 4 - Processes](#lab4)
- [Lab 5 - Signals](#lab5)
- [Lab 6 - Pipes](#lab6)
- [Lab 7 - IPC (Chat using Queues)](#lab7)
- [Lab 8 - IPC (Shared Memory with Semaphores)](#lab8)
- [Lab 9 - Threads](#lab9)
- [Lab 10 - Thread Synchronization](#lab10)
- [Lab 11 - TCP/IP Sockets](#lab11)
- [Lab 12 - UDP Sockets](#lab12)

## Lab 1 - Makefile

This lab introduces the use of `makefiles` for automating the compilation process. It helps in managing dependencies and creating build rules for C programs.

## Lab 2 - Libraries

In this lab, you will learn how to compile and link both static and shared libraries in C. It demonstrates the creation and usage of libraries to modularize code.

## Lab 3 - Files

This lab focuses on file management using system libraries. It teaches how to open, read, write, and close files programmatically in UNIX systems.

## Lab 4 - Processes

In this lab, you will learn how to create and manage UNIX processes using system calls such as `fork()`, `exec()`, and `wait()`.

## Lab 5 - Signals

This lab introduces UNIX signals and demonstrates how to send and handle them. You'll learn to use `kill()` and `signal()` functions to manage inter-process communication.

## Lab 6 - Pipes

In this lab, you'll explore inter-process communication (IPC) using pipes. It shows how two processes can exchange data through unnamed and named pipes.

## Lab 7 - IPC (Chat using Queues)

This lab demonstrates the use of message queues for inter-process communication. You'll create a simple chat program where processes can exchange messages.

## Lab 8 - IPC (Shared Memory with Semaphores)

In this lab, you'll learn how to manage memory shared between multiple processes using semaphores. It covers how to coordinate access to shared resources.

## Lab 9 - Threads

This lab introduces threads and demonstrates how to optimize programs using the POSIX threads library (`pthread`). As a case study, you'll parallelize Conway's Game of Life.

## Lab 10 - Thread Synchronization

In this lab, you'll implement thread synchronization mechanisms (mutexes, condition variables) to solve the Santa Claus problem. It emphasizes managing access to shared resources between threads.

## Lab 11 - TCP/IP Sockets

This lab covers the creation of a simple chat application using TCP/IP sockets. It demonstrates how to establish a connection, send, and receive messages between a client and server.

## Lab 12 - UDP Sockets

In this lab, you'll create a chat application using UDP sockets. You'll learn how to manage unreliable data transmission and handle messages between client and server.

## Requirements

- GCC compiler
- Make utility

Ensure you have these installed before compiling and running the programs.
