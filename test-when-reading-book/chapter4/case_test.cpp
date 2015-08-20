int main ()
{
   char c = 'h';

   switch (c) {
        case 'h':
            //int val = 10;   /* not allowed */
            int val;    /*it is ok*/
            break;
        case 'v':
            {
                int val = 10;   /* the better way */
            }
            break;
        default:
            break;

   }




}
