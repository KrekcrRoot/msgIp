#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <Imply.h>
#include <thread>
#include <windows.h>

unsigned short port = 18617;
bool monitoring = false;
string name {};
string chatIp {};

using namespace std;
using namespace boost::asio;

void getMode()
{
    while(true)
    {
        char mode {};
        cin >> mode;

        if(mode == 'c' || mode == 'm')
        {
            if(mode == 'm') monitoring = true;
            break;
        }

        cout << "Wrong mode, choose 'm' or 'c'" << endl;
    }
}

void getPort()
{
    while(true)
    {
        cout << "Choose port (default: 18617)" << endl;
        cin >> port;
        if(port > 65535 || port < 1000)
        {
            cout << "Wrong port: " << port << " != (1000; 65535)" << endl;
        }else{
            break;
        }
    }
}


void messagesSend()
{

    try {
        io_service io_service{};

        ip::udp::socket socket{io_service};
        socket.open(ip::udp::v4());

        ip::udp::endpoint endpoint{ip::address_v4::from_string(chatIp), port};

        while(true)
        {
            string msg {};
            getline(cin, msg);

            msg = "@" + Imply::encrypt(name + ": " +  msg);

            socket.send_to(buffer(msg), endpoint);
            cout << endl;
        }
    }catch(boost::system::system_error e)
    {
        cout << e.what();
    }


}

void getMessages()
{

    try
    {
        io_service io_service{};

        ip::udp::endpoint endpoint{ip::address_v4::from_string("0.0.0.0"), port};
        ip::udp::socket socket{io_service, endpoint};

        for(;;)
        {

            boost::array<char, 512> data{};

            boost::asio::ip::udp::endpoint sender_endpoint;
            socket.receive_from(
                    boost::asio::buffer(data, 512), sender_endpoint);

            string raw = data.data();

            if(raw[0] == '@')
            {
                raw = raw.substr(1);
                cout << Imply::decrypt(raw) << endl;
            }

        }
    }catch(std::exception e)
    {
        cout << e.what();
    }


}



int main() {

    SetConsoleOutputCP(CP_UTF8);

    cout << "____________________________" << endl;
    cout << "MsgIP | with Imply encryptor" << endl;
    cout << "For safety and clear ip msg" << endl;
    cout << "----------------------------" << endl << endl;

    cout << "Choose mode: monitoring or chatting (m/c)" << endl;

    getMode();

    if(monitoring)
    {

        getPort();

        io_service io_service{};

        ip::udp::endpoint endpoint{ip::address_v4::from_string("0.0.0.0"), port};
        ip::udp::socket socket{io_service, endpoint};

        for(;;)
        {

            boost::array<char, 512> data{};

            boost::asio::ip::udp::endpoint sender_endpoint;

            socket.receive_from(
                    boost::asio::buffer(data, 128), sender_endpoint);

            string raw = data.data();

            if(raw[0] == '@')
            {
                raw = raw.substr(1);
                cout << Imply::decrypt(raw) << endl;
            }

        }


    }

    cout << "Enter your name:" << endl;
    cin >> name;

    getPort();

    cout << "Enter ip address: " << endl;
    cin >> chatIp;



    thread chat{messagesSend};
    thread messages(getMessages);

    chat.join();
    messages.join();




    return 0;
}
