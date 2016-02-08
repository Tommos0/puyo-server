#ifndef NETWORK_H
#define NETWORK_H

class Connection {
    public:
        enum packet_type { 
            MOVE, REQUEST, CHAT
        };
        Connection();
        ~Connection();




};



#endif /* NETWORK_H */
