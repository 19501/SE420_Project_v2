#include <istream>

struct PPMObject
{
  std::string magicNum;
  int width, height, maxColVal;
  char * m_Ptr;
};

std::istream& operator >>(std::istream &inputStream, PPMObject &other);

std::ostream& operator <<(std::ostream &outputStream, const PPMObject &other);
