
#include <types.hxx>
    using kiss::char16;
    
#include <stdio.h>
#include <typeinfo>

int main()
{
    printf("%s\n", typeid(decltype(*u"")).name());
}