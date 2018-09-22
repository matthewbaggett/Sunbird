

class Debugger{
  public:
    Debugger(Stream &serial, WiFiUDP _udp);
    void printf(const char* fmt, ...);
    void println(const char* fmt, ...);
  private:
    Stream *_serial;
    WiFiUDP _udp;
};

Debugger::Debugger(Stream &serial, WiFiUDP udp){
  _serial = &serial;
  _udp = udp;
}

void Debugger::printf(const char* fmt, ...){
    _udp.beginPacketMulticast(ipMulti, portMulti, WiFi.localIP());
    va_list argv;
    va_start(argv, fmt);

    for (int i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%') {
            // Look for specification of number of decimal places
            int places = 2;
            if (fmt[i+1] >= '0' && fmt[i+1] <= '9') {
                places = fmt[i+1] - '0';
                i++;
            }
            
            switch (fmt[++i]) {
                case 'B':
                    _serial->print("0b");
                    _udp.print("0b"); // Fall through intended
                case 'b':
                    _serial->print(va_arg(argv, int), BIN);
                    _udp.print(va_arg(argv, int), BIN);
                    break;
                case 'c': 
                    _serial->print((char) va_arg(argv, int));
                    _udp.print((char) va_arg(argv, int));
                    break;
                case 'd': 
                case 'i':
                    _serial->print(va_arg(argv, int), DEC);
                    _udp.print(va_arg(argv, int), DEC);
                    break;
                case 'f': 
                    _serial->print(va_arg(argv, double), places);
                    _udp.print(va_arg(argv, double), places);
                    break;
                case 'l': 
                    _serial->print(va_arg(argv, long), DEC);
                    _udp.print(va_arg(argv, long), DEC);
                    break;
                case 'o':
                    _serial->print(va_arg(argv, int) == 0 ? "off" : "on");
                    _udp.print(va_arg(argv, int) == 0 ? "off" : "on");
                    break;
                case 's': 
                    _serial->print(va_arg(argv, const char*));
                    _udp.print(va_arg(argv, const char*));
                    break;
                case 'X':
                    _serial->print("0x"); // Fall through intended
                    _udp.print("0x"); // Fall through intended
                case 'x':
                    _serial->print(va_arg(argv, int), HEX);
                    _udp.print(va_arg(argv, int), HEX);
                    break;
                case '%': 
                    _serial->print(fmt[i]);
                    _udp.print(fmt[i]);
                    break;
                default:
                    _serial->print("?");
                    _udp.print("?");
                    break;
            }
        } else {
            _serial->print(fmt[i]);
            _serial->print("\n");
            _udp.print(fmt[i]);
        }
    }
    va_end(argv);
    _udp.endPacket();
}

