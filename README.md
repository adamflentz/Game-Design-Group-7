# House Haunters

![WOW](resources/hh.png)
Hunt or be Haunted

# Quick Design Guide

This is a design guide based on how the code looks already...for the most part.

## Casing
Classes/Filenames : PascalCase  
Methods/functions : camelCase  
Variable names    : snake_cased

## Include guard
`#ifndef` rather than `#pragma once`

## Comments
Comments in hpp files, should detail what a method does.
Comments in cpp files, if required, should detail how a method does what it do. 

## Brackets
For classes and functions start the bracket on the following line.
For loops and if statements, do whatever you feel is neater looking (we're not professionals okay).

## Namespaces 
Try not to 'use' any namespaces.  
So avoid things like: `using namespace std`


## Example 
(may or may not compile)

```cpp
// MyClass.hpp
#ifndef MYCLASS_HPP  
#define MYCLASS_HPP

#include <iostream>
#include <string>

class MyClass
{
public:

    void enthusiasticGreeting(int length);
private:
    std::string greeting = "Greetings";
};

#endif

// MyClass.cpp
#include "MyClass.hpp"

void MyClass::enthusiasticGreeting(int length)
{
    for(int i = 0; i < length; i++){
        std::cout << this->greeting << std::endl;
    }
}


```