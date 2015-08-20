using INT=int;

int gv = 0;

INT&
func ()
{
    return gv;
}

int main ()
{
    return func();
}
