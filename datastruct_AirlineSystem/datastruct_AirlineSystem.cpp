#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<Windows.h>
#include <locale>
#include"flight.h"
using namespace std;

FQueue flightQueue;  // 创建航班队列
CQueue bookedCustomers;// 创建客户队列
CQueue waitingCustomers;

FNode findFlight(FQueue& F, const string& flightNumber);
void loadFlightTxt();             // 加载航班数据
void loadCustomersTxt();          // 加载客户数据
void assignCustomersToFlights();  // 分配每个飞机的客户到飞机的success和waiting队列
void search();                    // 查询
void book();                      //订票
void cancel();                    // 退票
void sort(FQueue& flightQueue);   //排序 
void system();


int main() {
    init_fqueue(flightQueue);
    init_cqueue(bookedCustomers);
    init_cqueue(waitingCustomers);

    // 加载初始数据
    loadFlightTxt();
    loadCustomersTxt();
    assignCustomersToFlights();

    system();
}

//加载flight.txt
void loadFlightTxt()
{
    init_fqueue(flightQueue);  // 初始化队列

    ifstream infile("flight02.txt"); // 打开文件
    if (!infile) { // 判断文件是否成功打开
        cerr << "Error: Unable to open flight.txt!" << endl;
        exit(0);
    }

    string line;
    while (getline(infile, line)) { // 按行读取文件内容
        stringstream ss(line); // 使用 stringstream 解析每行数据
        Flight flight;

        // 从当前行解析字段
        ss >> flight.Destination;
        ss >> flight.Flight_number;
        ss >> flight.Aircraft_number;
        ss >> flight.Date;
        ss >> flight.Capacity;
        ss >> flight.Remaining_Tickets;

        init_cqueue(flight.success);
        init_cqueue(flight.waiting);
        // 将解析后的航班信息入队
        Push_fqueue(flightQueue, flight);
    }

    infile.close(); // 关闭文件

    // 显示队列中的航班信息
    //display_fqueue(flightQueue);

}

//加载customers.txt
void loadCustomersTxt()
{
    //格式：姓名 仓位 票数 航班号 日期 是否候补
    init_cqueue(bookedCustomers); 
    init_cqueue(waitingCustomers); 

    ifstream infile("customers02.txt"); // 打开文件
    if (!infile) { // 判断文件是否成功打开
        cerr << "Error: Unable to open flight.txt!" << endl;
        exit(0);
    }

    string line;
    while (getline(infile, line)) { // 按行读取
        stringstream ss(line); 
        Cus cus;

        // 从当前行解析字段
        ss >> cus.name;
        ss >> cus.fclass;
        ss >> cus.tickets;
        ss >> cus.Flight_number;
        ss >> cus.Date;
        ss >> cus.isWaiting;

        if (cus.isWaiting == 1)//分组加入已购票和候补队列
        {
            Push_cqueue(waitingCustomers, cus);
        }
        else if (cus.isWaiting == 0)
        {
            Push_cqueue(bookedCustomers, cus);
        }


    }

    infile.close(); // 关闭文件
}

// 根据客户的航班号找到对应航班
FNode findFlight(FQueue& F, const string& flightNumber) {
    FNode temp = F.head; // 从队列头开始
    while (temp != nullptr) {
        if (temp->Flight.Flight_number == flightNumber) {
            return temp; // 找到目标航班，返回节点
        }
        temp = temp->next; // 遍历下一个节点
    }
    return nullptr; // 未找到航班
}

//给每个航班的success和waiting队列分配客户
void assignCustomersToFlights() {
    CNode bookedTemp = bookedCustomers.head;
    while (bookedTemp != nullptr) {
        FNode flight = findFlight(flightQueue, bookedTemp->customer.Flight_number);
        if (flight != nullptr) {
            // 将客户加入航班的 success 队列
            Push_cqueue(flight->Flight.success, bookedTemp->customer);
        }
        else {
            cout << "Error: Flight " << bookedTemp->customer.Flight_number
                << " not found for customer " << bookedTemp->customer.name << endl;
        }
        bookedTemp = bookedTemp->next;
    }

    // 遍历候补队列
    CNode waitingTemp = waitingCustomers.head;
    while (waitingTemp != nullptr) {
        FNode flight = findFlight(flightQueue, waitingTemp->customer.Flight_number);
        if (flight != nullptr) {
            // 将客户加入航班的 waiting 队列
            Push_cqueue(flight->Flight.waiting, waitingTemp->customer);
        }
        else {
            cout << "Error: Flight " << waitingTemp->customer.Flight_number
                << " not found for customer " << waitingTemp->customer.name << endl;
        }
        waitingTemp = waitingTemp->next;
    }
}


//查询功能
void searchDestination(const string& Destination) {
    cout << "Searching for flights to '" << Destination << "'..." << endl;
    Sleep(500);

    FQueue Ftemp;
    init_fqueue(Ftemp);
    FNode temp = flightQueue.head;
    bool isfound = false;

    while (temp != nullptr) {
        // 检查目的地和日期是否匹配
        if (temp->Flight.Destination == Destination ) {
            Push_fqueue(Ftemp,temp->Flight); // 显示匹配的航班信息
            isfound = true;
        }
        temp = temp->next;
    }
    display_ALLfqueue(Ftemp);
    // 如果未找到匹配的航班
    if (!isfound) {
        cout << "No flights found for destination '" << Destination
            << "'." << endl;
    }
}
void searchDestinationDate(const string& Destination, const string& Date) {
    cout << "Searching for flights to '" << Destination << "' on '" << Date << "'..." << endl;
    Sleep(500);

    FNode temp = flightQueue.head;
    bool isfound = false; 

    while (temp != nullptr) {
        // 检查目的地和日期是否匹配
        if (temp->Flight.Destination == Destination && temp->Flight.Date == Date) {
            display_flight(temp->Flight); // 显示匹配的航班信息
            isfound = true;
        }
        temp = temp->next;
    }

    // 如果未找到匹配的航班
    if (!isfound) {
        cout << "No flights found for destination '" << Destination
            << "' on date '" << Date << "'." << endl;
    }
}
//查询
void search() {
    int searchChoice;
    cout << "========== Search Flights ==========" << endl;
    cout << "1. Search flights by destination and date" << endl;
    cout << "2. Search flights by destination " << endl;
    cout << "3. View all available flights" << endl;
    cout << "Enter your choice (1 , 2 or 3): ";
    cin >> searchChoice;

    if (searchChoice == 1) {
        string destination, date;

        cout << "Enter Destination: ";
        cin >> destination;
        cout << "Enter Date (e.g., YYYYMMDD): ";
        cin >> date;

        if (destination.empty() || date.empty()) {
            cout << "Error: Destination and Date cannot be empty!" << endl;
            cout << "=====================================" << endl;
            return;
        }

        cout << "\nYou are searching for flights with the following details:" << endl;
        cout << "Destination: " << destination << endl;
        cout << "Date: " << date << endl;

        char confirm;
        cout << "Confirm search? (Y/N): ";
        cin >> confirm;

        if (confirm != 'Y' && confirm != 'y') {
            cout << "Search process aborted." << endl;
            cout << "=====================================" << endl;
            return;
        }

        cout << "Searching for flights..." << endl;
        searchDestinationDate(destination, date);

    }
    else if (searchChoice == 2) {
        string destination, date;

        cout << "Enter Destination: ";
        cin >> destination;

        if (destination.empty() ) {
            cout << "Error: Destination and Date cannot be empty!" << endl;
            cout << "=====================================" << endl;
            return;
        }

        cout << "\nYou are searching for flights with the following details:" << endl;
        cout << "Destination: " << destination << endl;

        char confirm;
        cout << "Confirm search? (Y/N): ";
        cin >> confirm;

        if (confirm != 'Y' && confirm != 'y') {
            cout << "Search process aborted." << endl;
            cout << "=====================================" << endl;
            return;
        }

        cout << "Searching for flights..." << endl;
        searchDestination(destination);

    }
    else if (searchChoice == 3) {
        // 查看所有航班
        cout << "Displaying all available flights:" << endl;
        display_ALLfqueue(flightQueue);

    }
    else {
        cout << "Invalid choice! Please enter 1 or 2." << endl;
        cout << "=====================================" << endl;
        return;
    }

    // 询问是否订票
    char bookChoice;
    cout << "\nDo you want to book a ticket? (Y/N): ";
    cin >> bookChoice;

    if (bookChoice == 'Y' || bookChoice == 'y') {
        cout << "Redirecting to booking system..." << endl;
        book();
    }
    else {
        cout << "Returning to main menu." << endl;
    }

    // 结束输出
    cout << "=====================================" << endl;
}



//订票功能
void bookTicket(Cus C) {
    FNode F = findFlight(flightQueue, C.Flight_number);
    if (F == nullptr) {
        cout << "Flight not found! Booking failed." << endl;
        return;
    }

    ofstream customerFile("customers02.txt", ios::app); 

    if (!customerFile.is_open()) {
        cout << "Error: Unable to open customers.txt for writing." << endl;
        return;
    }

    if (F->Flight.Remaining_Tickets > 0) {// 添加到成功购票队列
        Push_cqueue(F->Flight.success, C); 
        F->Flight.Remaining_Tickets--;   

        customerFile << C.name << " " << C.fclass << " " << C.tickets << " "
            << C.Flight_number << " " << C.Date << " " << 0 << endl;

        cout << "Booking......" << endl;
        Sleep(500);
        cout << "Booking successful! Ticket recorded in customers.txt." << endl;
    }
    else {
        char choice;
        cout << "The flight is full. Would you like to join the waiting list? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            Push_cqueue(F->Flight.waiting, C); // 添加到候补队列

            // 写入候补信息到文件
            if (customerFile.is_open()) {
                customerFile << C.name << " " << C.fclass << " " << C.tickets << " "
                    << C.Flight_number << " " << C.Date << " " << 1 << endl;
            }
            else {
                cout << "Error: Unable to open customers.txt for writing." << endl;
            }

            cout << "Added to waiting list and recorded in customers.txt." << endl;
        }
        else {
            cout << "You chose not to join the waiting list. No further action taken." << endl;
        }
    }
    assignCustomersToFlights();//更新每个航班的两个客户队列
    customerFile.close(); 
}
//订票
void book() {
    // 输出功能标题
    cout << "========== Book Ticket ==========" << endl;

    // 创建客户信息结构体
    Cus customerToBook;
    string flightNumber;

    // 输入客户信息
    cout << "Enter Customer Name: ";
    cin >> customerToBook.name;

    cout << "Enter Flight Class (e.g., Economy, Business: 3, 2...): ";
    cin >> customerToBook.fclass;

    cout << "Enter Number of Tickets: ";
    cin >> customerToBook.tickets;

    cout << "Enter Flight Number: ";
    cin >> flightNumber;
    customerToBook.Flight_number = flightNumber;

    // 输入日期
    cout << "Enter Flight Date (YYYYMMDD): ";
    cin >> customerToBook.Date;

    // 确认输入的信息
    cout << "\nYou are booking the following ticket(s):" << endl;
    cout << "Name: " << customerToBook.name << endl;
    cout << "Flight Class: " << customerToBook.fclass << endl;
    cout << "Number of Tickets: " << customerToBook.tickets << endl;
    cout << "Flight Number: " << customerToBook.Flight_number << endl;
    cout << "Flight Date: " << customerToBook.Date << endl;

    char confirm;
    cout << "Confirm booking? (Y/N): ";
    cin >> confirm;

    // 检查用户确认
    if (confirm != 'Y' && confirm != 'y') {
        cout << "Booking process aborted." << endl;
        cout << "==================================" << endl;
        return;
    }

    // 调用核心功能函数
    bookTicket(customerToBook);
    loadCustomersTxt();//更新
    assignCustomersToFlights();
    // 结束输出
    cout << "==================================" << endl;
}


//删除一个客户
bool deleteCustomers(CQueue& Cqueue, Cus C) {
    CNode pre = nullptr;
    CNode cur = Cqueue.head;

    while (cur != nullptr) {
        if (cur->customer.name == C.name && cur->customer.Date == C.Date) {
            if (pre == nullptr) { 
                Cqueue.head = cur->next;
            }
            else {//如果pre非空则保存cur的next指针
                pre->next = cur->next;
            }
            if (cur == Cqueue.rear) { 
                Cqueue.rear = pre;
            }
            delete cur; 
            Cqueue.count--; // 更新队列长度
            return true; 
        }
        pre = cur;
        cur = cur->next;
    }
    return false; 
}
//文档里删除一个客户
void deleteCustomersTxt(Cus C) {
    ifstream inFile("customers02.txt");
    if (!inFile.is_open()) {
        cerr << "Error: Could not open customers.txt for reading." << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        cerr << "Error: Could not open temp.txt for writing." << endl;
        inFile.close();
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        istringstream iss(line);
        string name, flightNumber, date;
        int fclass, tickets, isWaiting;

        // 按格式读取一条记录
        if (iss >> name >> fclass >> tickets >> flightNumber >> date >> isWaiting) {
            if (name == C.name &&  date == C.Date) {
                found = true; // 找到目标记录，不写入临时文件
            }
            else {
                tempFile << line << endl; // 不匹配的记录写入临时文件
            }
        }
        else {
            // 如果行格式错误，直接跳过
            cerr << "Warning: Malformed line in customers.txt: " << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // 替换原文件
    if (found) {
        if (remove("customers02.txt") != 0 || rename("temp.txt", "customers02.txt") != 0) {
            cerr << "Error: Could not replace customers.txt with updated data." << endl;
        }
        else {
            cout << "Customer record successfully deleted from customers02.txt." << endl;
        }
    }
    else {
        cout << "No matching record found in customers.txt for deletion." << endl;
        // 删除临时文件
        remove("temp.txt");
    }
}
//删除功能
void cancelTicket(Cus C) {
    FNode F = findFlight(flightQueue, C.Flight_number);
    if (F == nullptr) {
        cout << "Error: Flight not found for cancellation." << endl;
        return;
    }

    // 尝试从成功购票队列中移除
    if (C.isWaiting==0) {
        deleteCustomers(F->Flight.success, C);
        deleteCustomers(bookedCustomers, C);
        // 更新余票
        F->Flight.Remaining_Tickets += C.tickets;
        

        // 从 customers.txt 文件中删除该客户的购票记录
        deleteCustomersTxt(C);

        cout << "Ticket successfully canceled. Updated flight availability." << endl;

        // 检查候补队列是否有客户可以顶替
        while (F->Flight.waiting.head != nullptr) {
            CNode firstWaiting = F->Flight.waiting.head;

            // 判断当前余票是否能满足候补客户需求
            if (F->Flight.Remaining_Tickets >= firstWaiting->customer.tickets) {
                // 从候补队列中移除该客户
                F->Flight.waiting.head = firstWaiting->next;
                if (F->Flight.waiting.head == nullptr) {
                    F->Flight.waiting.rear = nullptr; // 候补队列为空
                }
                F->Flight.waiting.count--;

                // 更新候补客户的状态为成功购票
                firstWaiting->customer.isWaiting = 0;

                // 加入成功购票队列
                Push_cqueue(F->Flight.success, firstWaiting->customer);
                F->Flight.Remaining_Tickets -= firstWaiting->customer.tickets;

                // 同步将客户加入 bookedCustomers 队列
                Push_cqueue(bookedCustomers, firstWaiting->customer);

                // 将候补客户信息更新至 customers.txt 文件
                deleteCustomersTxt(firstWaiting->customer); // 删除候补记录
                ofstream customerFile("customers.txt", ios::app);
                customerFile << firstWaiting->customer.name << " "
                    << firstWaiting->customer.fclass << " "
                    << firstWaiting->customer.tickets << " "
                    << firstWaiting->customer.Flight_number << " "
                    << firstWaiting->customer.Date << " "
                    << 0 << endl; 
                customerFile.close();

                cout << "Customer " << firstWaiting->customer.name << " moved from waiting list to success list." << endl;

                delete firstWaiting; 
                break; 
            }
            else {
                // 余票不足
                char confirm;
                cout << "Customer " << firstWaiting->customer.name << ", the available tickets ("
                    << F->Flight.Remaining_Tickets << ") are less than your request ("
                    << firstWaiting->customer.tickets << "). Would you like to book the available tickets? (Y/N): ";
                cin >> confirm;

                if (confirm == 'Y' || confirm == 'y') {
                    // 修改候补客户的票数为当前余票
                    firstWaiting->customer.tickets = F->Flight.Remaining_Tickets;

                    // 从候补队列中移除该客户
                    F->Flight.waiting.head = firstWaiting->next;
                    if (F->Flight.waiting.head == nullptr) {
                        F->Flight.waiting.rear = nullptr; // 候补队列为空
                    }
                    F->Flight.waiting.count--;

                    // 更新候补客户的状态为成功购票
                    firstWaiting->customer.isWaiting = 0;

                    // 加入成功购票队列
                    Push_cqueue(F->Flight.success, firstWaiting->customer);
                    F->Flight.Remaining_Tickets = 0; // 更新余票

                    // 同步将客户加入 bookedCustomers 队列
                    Push_cqueue(bookedCustomers, firstWaiting->customer);

                    // 将候补客户信息更新至 customers.txt 文件
                    deleteCustomersTxt(firstWaiting->customer); // 删除候补记录
                    ofstream customerFile("customers.txt", ios::app);
                    customerFile << firstWaiting->customer.name << " "
                        << firstWaiting->customer.fclass << " "
                        << firstWaiting->customer.tickets << " "
                        << firstWaiting->customer.Flight_number << " "
                        << firstWaiting->customer.Date << " "
                        << 0 << endl; // 更新候补客户为成功购票
                    customerFile.close();

                    cout << "Customer " << firstWaiting->customer.name << " moved from waiting list to success list with modified ticket count." << endl;

                    delete firstWaiting; // 释放候补节点内存
                    break; // 找到满足的候补客户后退出循环
                }
                else {
                    // 当前客户不愿意接受，继续处理下一个候补客户
                    F->Flight.waiting.head = firstWaiting->next;
                    if (F->Flight.waiting.head == nullptr) {
                        F->Flight.waiting.rear = nullptr; // 候补队列为空
                    }
                    F->Flight.waiting.count--;

                    cout << "Customer " << firstWaiting->customer.name << " declined the offer. Moving to the next customer." << endl;

                    delete firstWaiting; // 释放候补节点内存
                }
            }
        }
    }

    // 尝试从候补队列中移除
    if (C.isWaiting) {
        deleteCustomers(F->Flight.waiting, C);
        deleteCustomers(waitingCustomers, C);

        // 从 customers.txt 文件中删除候补记录
        deleteCustomersTxt(C);

        cout << "Customer removed from the waiting list." << endl;
    }
    else {
        cout << "No matching customer found in either the success or waiting list." << endl;
    }
}

//删除
void cancel() {
    cout << "========== Cancel Ticket ==========" << endl;

    // 获取用户输入
    Cus customerToCancel;
    cout << "Enter Customer Name: ";
    cin >> customerToCancel.name;

    cout << "Enter Flight Number: ";
    cin >> customerToCancel.Flight_number;

    cout << "Enter Ticket Count: ";
    cin >> customerToCancel.tickets;

    cout << "Enter Flight Date (YYYYMMDD): ";
    cin >> customerToCancel.Date;

    // 确认
    cout << "\nYou are canceling the following ticket(s):" << endl;
    cout << "Name: " << customerToCancel.name << endl;
    cout << "Flight Number: " << customerToCancel.Flight_number << endl;
    cout << "Ticket Count: " << customerToCancel.tickets << endl;
    cout << "Flight Date: " << customerToCancel.Date << endl;

    char confirm;
    cout << "Confirm cancellation? (Y/N): ";
    cin >> confirm;

    if (confirm != 'Y' && confirm != 'y') {
        cout << "Cancellation process aborted." << endl;
        return;
    }
    // 核心功能
    cancelTicket(customerToCancel);

    //更新几个客户队列
    loadCustomersTxt();
    assignCustomersToFlights();
    cout << "===================================" << endl;
}

//按日期排序
void sort(FQueue& flightQueue) {
    if (flightQueue.head == nullptr || flightQueue.head->next == nullptr) {
        return; // 空队列或只有一个节点，无需排序
    }

    // 将链表转换为数组以便于索引
    vector<FNode> flightArray;
    FNode current = flightQueue.head;
    while (current != nullptr) {
        flightArray.push_back(current);
        current = current->next;
    }

    // 开始希尔排序
    size_t n = flightArray.size();
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i++) {
            FNode temp = flightArray[i];
            size_t j = i;

            // 按日期比较，日期为字符串形式，直接字典序比较
            while (j >= gap && flightArray[j - gap]->Flight.Date > temp->Flight.Date) {
                flightArray[j] = flightArray[j - gap];
                j -= gap;
            }
            flightArray[j] = temp;
        }
    }

    // 将数组重新转换为链表
    flightQueue.head = flightArray[0];
    current = flightQueue.head;
    for (size_t i = 1; i < n; i++) {
        current->next = flightArray[i];
        current = current->next;
    }
    flightQueue.rear = current;
    current->next = nullptr; // 确保尾节点指向 nullptr
}

//系统
void system() {
    int choice;

    do {
        // 菜单显示
        cout << "=========================================" << endl;
        cout << "       Welcome to Airline System         " << endl;
        cout << "=========================================" << endl;
        cout << "1. Search Flights                        " << endl;
        cout << "2. Book Tickets                          " << endl;
        cout << "3. Cancel Tickets                        " << endl;
        cout << "4. Sort Flight                           " << endl;
        cout << "5. Exit System                           " << endl;
        cout << "=========================================" << endl;
        cout << "Please enter your choice (1-4): ";
        cin >> choice;

        // 用户输入处理
        switch (choice) {
        case 1:
            cout << "\n[Search Flights]\n";
            search();
            break;
        case 2:
            cout << "\n[Book Tickets]\n";
            book();
            break;
        case 3:
            cout << "\n[Cancel Tickets]\n";
            cancel();
            break;
        case 4:
            cout << "\n[Sort Flight]\n";
            sort(flightQueue);
            break;
        case 5:
            cout << "\nExiting the system. Thank you for using Airline System!\n";
            exit(0);
        default:
            cout << "\nInvalid choice! Please enter a number between 1 and 4.\n";
        }

        // 添加空行以美化输出
        cout << endl;

    } while (choice != 5);  // 当用户选择4时退出循环
}


