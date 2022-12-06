/*****************************
*                            * 
*  Кофф Даниил ПИ-221        *
*  Арифметика длинных чисел  *
*                            *
*****************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  string input1;
  string input2;
  string operation;
  vector <int> conversion1;
  vector <int> conversion2;
  vector <int> output;
  vector <int> divBuffer;
  int index1;
  int index2;
  int buffer = 0;
  
  cout << "Enter first value: ";
  getline(cin, input1);
  
  for (int index = 0; index < input1.length(); ++index) {
    if (!isdigit(input1[index])) {
      cout << "Invalid input";
      return 0;
    }
    
    conversion1.push_back(input1[index] - '0');
  }
  
  cout << "Enter operation: ";
  getline(cin, operation);
  
  if (operation != "+" && operation != "-" && operation != "*" && operation != "/" && operation != ">" && operation != "<" && operation != "=") {
    cout << "Invalid input";
    return 0;
  }
  
  cout << "Enter second value: ";
  getline(cin, input2);
  
  for (int index = 0; index < input2.length(); ++index) {
    if (!isdigit(input2[index])) {
      cout << "Invalid input";
      return 0;
    }
    
    conversion2.push_back(input2[index] - '0');
  }
  
  cout << "\nResult: ";
  
  if (conversion1.size() > conversion2.size()) {
    for (int index = 0; index < conversion1.size() - conversion2.size(); ++index) {
      conversion2.insert(conversion2.begin(), 0);
    }
  }
  if (conversion1.size() < conversion2.size()) {
    for (int index = 0; index < conversion2.size() - conversion1.size(); ++index) {
      conversion1.insert(conversion1.begin(), 0);
    }
  }
  
  if (operation == "=") {
    for (int index = 0; index < conversion1.size(); ++index) {
      if (conversion1[index] != conversion2[index]) {
        buffer = 0;
        break;
      }
      else {
        buffer = 1;
      }
    }
    
    cout << buffer;
  }
  
  if (operation == "<") {
    for (int index = 0; index < conversion1.size(); ++index) {
      if (conversion1[index] < conversion2[index]) {
        buffer = 1;
        break;
      }
      else if (conversion1[index] > conversion2[index]) {
        buffer = 0;
        break;
      }
      else {
        buffer = 0;
      }
    }
  }
  
  if (operation == ">") {
    for (int index = 0; index < conversion1.size(); ++index) {
      if (conversion1[index] > conversion2[index]) {
        buffer = 1;
        break;
      }
      else if (conversion1[index] < conversion2[index]) {
        buffer = 0;
        break;
      }
      else {
        buffer = 0;
      }
    }
  }
  
  if (operation == "+") {
    for (int index = conversion1.size() - 1; index >= 0; --index) {
      output.insert(output.begin(), conversion1[index] + conversion2[index]);
      
      if (output.size() > 1) {
        output[0] += output[1] / 10;
        output[1] %= 10;
      }
    }
    
    for (int index = 0; index < output.size(); ++index) {
      cout << output[index];
    }
  }
  
  if (operation == "-") {
    for (int index = 0; index < conversion1.size(); ++index) {
      if (conversion1[index] > conversion2[index]) {
        buffer = 1;
        break;
      }
      if (conversion1[index] < conversion2[index]) {
        buffer = -1;
        break;
      }
    }
    
    if (buffer == 0) {
      cout << 0;
      return 0;
    }
    
    if (buffer == 1) {
      for (int index = conversion1.size() - 1; index >= 0; --index) {
        output.insert(output.begin(), conversion1[index] - conversion2[index]);
        
        if (output.size() > 1) {
          if (output[1] < 0) {
            output[0] -= 1;
            output[1] += 10;
          }
        }
      }
    }
    
    if (buffer == -1) {
      for (int index = conversion1.size() - 1; index >= 0; --index) {
        output.insert(output.begin(), conversion2[index] - conversion1[index]);
        
        if (output.size() > 1) {
          if (output[1] < 0) {
            output[0] -= 1;
            output[1] += 10;
          }
        }
      }
      
      cout << "-";
    }
    
    for (int index = 0; index < output.size(); ++index) {
      cout << output[index];
    }
  }
  
  if (operation == "*") {
    // I'm not gonna sugarcoat it. This bullshit was rewritten like 20 times already before it worked.
    while (output.size() < conversion1.size() + conversion2.size()) {
      output.push_back(0);
    }
    
    for (index1 = conversion1.size(); index1 > 0; --index1) {
      for (index2 = conversion2.size(); index2 > 0; -- index2) {
        output[index1 + index2 - 1] += conversion1[index1 - 1] * conversion2[index2 - 1];
        if (output[index1 + index2 - 1] >= 10) {
          output[index1 + index2 - 2] += output[index1 + index2 - 1] / 10;
          output[index1 + index2 - 1] %= 10;
        } 
      }
    }
    
    for (int index = 0; index < output.size(); ++index) {
      if (output[index] != 0) {
        buffer = 1;
      }
      
      if (buffer == 1) {
        cout << output[index];
      }
    }
  }
  
  if (operation == "/") {
    output.insert(output.begin(), 0);
    while (buffer == 0) {
      if (divBuffer.size() < conversion2.size()) {
        for (int index = 0; index < conversion2.size(); ++index) {
          divBuffer.insert(divBuffer.end(), conversion2[index]);
        }
      }
      else {
        for (int index = conversion2.size() - 1; index >= 0; --index) {
          divBuffer[divBuffer.size() - conversion2.size() + index] += conversion2[index];
        }
        
        for (int index = divBuffer.size() - 1; index >= 0; -- index) {
          if (divBuffer[index] >= 10) {
            if (index == 0) {
              divBuffer.insert(divBuffer.begin(), divBuffer[0] / 10);
              divBuffer[index + 1] %= 10;
            }
            else {
              divBuffer[index - 1] += divBuffer[index] / 10;
              divBuffer[index] %= 10;
            }
          }
        }
      }
      
      if (divBuffer.size() == conversion1.size()) {
        for (int index = 0; index < conversion1.size(); ++index) {
          if (conversion1[index] < divBuffer[index]) {
            buffer = 1;
            break;
          }
          else if (conversion1[index] > divBuffer[index]) {
            buffer = 0;
            break;
          }
          else {
            buffer = 0;
          }
        }
      }
      else if (divBuffer.size() > conversion1.size()) {
        buffer = 1;
      }
      
      if (buffer == 0) {
        output[output.size() - 1] += 1;
        for (int index = output.size() - 1; index >= 0; --index) {
          if (output[index] >= 10) {
            if (index == 0) {
              output.insert(output.begin(), output[0] / 10);
              output[index + 1] %= 10;
            }
            else {
              output[index - 1] += output[index] / 10;
              output[index] %= 10;
            }
          }
        }
      }
    }
    for (int index = 0; index < output.size(); ++index)
    cout << output[index];
  }

  return 0;
}

