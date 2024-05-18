/**
 * @file Test.h
 *
 * @brief Test Base Class for Unit Testing Framework.
 *
 * This header file declares the Test base class, which is an essential part of the unit testing framework
 * designed for verifying the correctness and functionality of various components in the project. The Test
 * class provides a generic interface for running individual tests, managing test outcomes (pass/fail), and
 * aggregating test results. It utilizes templates to allow any derived test class to execute its specific
 * test methods. The framework captures exceptions as test failures, reporting the reason for each failure
 * alongside the test's name. It concludes with a summary of all tests run, including the total number of
 * tests, passed tests, and failed tests.
 *
 * Usage:
 * Derived classes should implement the `runTests` method to execute their specific test cases using the
 * `runTest` method. This structure allows for flexible and extensive testing across various functionalities
 * within the project.
 *
 * @date Created on March 21, 2024.
 *
 * @authors
 * Advanced Programming Group Radix Sort:
 *   - Benjamin Duncan (edsml-bd1023)
 *   - Boyang Hu (edsml-bh223)
 *   - Chawk Chamoun (edsml-cc8915)
 *   - Mingsheng Cai (acse-sc4623)
 *   - Moyu Zhang (acse-mz223)
 *   - Ryan Benney (acse-rgb123)
 */

#pragma once

#include <iostream>
#include <string>
#include <exception>

class Test {
public:
    /**
     * Constructor
     *
     * Initializes a Test object. This constructor is primarily used for setting up initial conditions for unit tests.
     */
    Test() {}

    /**
     * Virtual Destructor
     *
     * Cleans up resources used by the Test object. Being virtual ensures that destructors in derived classes are called,
     * allowing for proper cleanup of any resources allocated during the test.
     */
    virtual ~Test() {}

    /**
     * Runs a Specific Test Function
     *
     * Executes a single test function within the context of a derived test class. This template method allows for flexible
     * testing of various functionalities by calling specific test methods defined in derived classes. The method captures
     * exceptions thrown during the test execution to differentiate between passed and failed tests, incrementing the
     * corresponding counters and printing the test result to the console.
     *
     * @tparam TestClass The derived class type from Test which contains the test function to be executed.
     * @tparam TestFunc The function pointer type to the test function to be executed.
     * @param testFunc The test function to be executed.
     * @param testName The name of the test, used for generating test output.
     */
    template<typename TestClass, typename TestFunc>
    void runTest(TestFunc testFunc, const std::string &testName) {
        std::cout << "Starting test: " << testName << std::endl;
        try {
            (static_cast<TestClass *>(this)->*testFunc)();
            std::cout << "Test passed: " << testName << std::endl;
            totalTestsPassed++;
        } catch (const std::exception &e) {
            std::cout << "Test failed: " << testName << " - Reason: " << e.what() << std::endl;
            totalTestsFailed++;
        }
        totalTestsRun++;
    }

    /**
     * Runs All Tests
     *
     * A pure virtual function that must be implemented by derived classes to execute their suite of test functions.
     * It orchestrates the running of all tests defined within a derived class, leveraging the runTest template method.
     */
    virtual void runTests() = 0;

    /**
     * Summarizes Test Results
     *
     * Outputs a summary of the test results, including the total number of tests run, the number of tests that passed,
     * and the number of tests that failed. This static method provides a global overview of the testing outcomes after
     * all tests have been executed.
     */
    static void summarize() {
        std::cout << "Tests completed. Total: " << totalTestsRun
                  << ", Passed: " << totalTestsPassed
                  << ", Failed: " << totalTestsFailed << std::endl;
    }

protected:
    static int totalTestsRun; // Total number of tests run
    static int totalTestsPassed; // Total number of tests passed
    static int totalTestsFailed; // Total number of tests failed
};

// Initialize static member variables
int Test::totalTestsRun = 0;
int Test::totalTestsPassed = 0;
int Test::totalTestsFailed = 0;
