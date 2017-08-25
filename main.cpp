#include <string>
#include <yatbcpp/yatbcpp.h>


yatbcpp::Token token("replace me with a usefull token");
yatbcpp::Bot B(token);

void update_callback(yatbcpp::Message M){
    std::string message= "Hallo " ;
    if( M.getFrom() ){
        message += M.getFrom().value().getFirst_name();
    }
    else{
        message += "Welt";
    }
    yatbcpp::sendMessage sendMessage(M.getChat(),message);
    B.send(sendMessage);
}

int main() {
    using namespace yatbcpp;

    B.addOnMessageListener(update_callback);
//
    B.startUpdating();
    B.startLongPoll();

    B.join();
    return 0;
}