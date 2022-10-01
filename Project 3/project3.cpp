// #include "sequence.h"
// #include <iostream>
// #include <string>

// void MemTest();
// int main()
// {
//    // Sequence mySequence(3);
//    // mySequence[0] = 5;
//    // cout << mySequence << endl;
//    // mySequence.insert(1, 3);
//    // MemTest();
//    // cout << "Check now";
//    Sequence data1(5);
//    Sequence data2(0);

//    for (int i = 0; i < 5; i++)
//    {
//       data1[i] = (i + 1) * 100;
//    }

//    data2 = data1;

//    data2[0] = 1;
//    data2[1] = 2;

//    cout << "Data1:      " << data1 << endl;
//    cout << "Data2:      " << data2 << endl;
//    cout << "Should be:  <100, 200, 300, 400, 500>" << endl;
//    cout << "            <1, 2, 300, 400, 500>" << endl
//         << endl;
//    // mySequence.insert(3, 100);
//    // mySequence.insert(5, 200);
//    // mySequence.push_back(50);
//    // // mySequence.clear();
//    // // mySequence.traverser();
//    // // cout << mySequence << endl;
//    // // mySequence.pop_back();
//    // mySequence.push_back(5);
//    // cout << mySequence << endl;

//    // Sequence secondSequence;
//    // secondSequence = mySequence;
//    // cout << secondSequence << endl;

//    // secondSequence.erase(0, secondSequence.size());
//    // cout << secondSequence << endl;
//    // secondSequence.push_back(5);
//    // cout << secondSequence << endl;
//    // mySequence.traverser();
// }

// void MemTest()
// {
//    Sequence s(500000);
//    for (int i = 0; i < 500000; i++)
//    {
//       s[i] = i;
//    }
//    cout << "Check memory" << endl;
// }