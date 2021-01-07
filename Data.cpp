#include "Data.h"


namespace zsj {

Data::Data(global::DataType dataType)
    :dataType(dataType)
{

}

global::DataType Data::getDataType() const
{
    return dataType;
}


Data::~Data()
{

}

}


