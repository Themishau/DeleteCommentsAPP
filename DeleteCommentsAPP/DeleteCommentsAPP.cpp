// DeleteCommentsAPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DeleteComments.h"

using namespace std;
bool fnRemoveComments(string InputFile, string OutputFile)
{
    string Textfile;
    regex CommentBlock("/\\*[^*]*\\*+(?:[^/*][^*]*\\*+)*/");
    /*regex CommentBlock_old("\\/\\*(.|[\\r\\n])*?\\*\\/");*/
    regex CommentBlockRest("\\*/");
    regex CommentInString("'~/\\*");
    regex CommentInComment("' \\*/':U");
    regex CommentLine("/\\*.*\\*/");
    regex CommentStars("\\*\\*");
    /*regex CommentBlock("\\/\\*.*\\*\\/");*/
    smatch matched;
    string s;

    ifstream TestfileInput;
    ofstream TestfileOutput;
    int iCommentCounter = 0;
    try {

        TestfileInput.open(InputFile);
        TestfileOutput.open(OutputFile);
        if (TestfileInput.is_open())
        {
            /* get position of end and beginning -> size of file */
            /* this would be the long version:                   */
            /*
             TestfileInput.seekg (0, is.end);
             int length = TestfileInput.tellg();
             TestfileInput.seekg (0, is.beg);

             allocate memory:
             char * buffer = new char [length];
            */
            /* get end position of file */
            TestfileInput.seekg(0, std::ios::end);
            /* reserve the amount of bits of TestfileInput (at the position tellg -> end)*/
            Textfile.reserve(TestfileInput.tellg());
            /* get start position of file */
            TestfileInput.seekg(0, std::ios::beg);
            /* assign to Textfile */
            Textfile.assign((istreambuf_iterator<char>(TestfileInput)),
                istreambuf_iterator<char>());

            /* replace Comments with "" */            

            /* sometimes there are comments in strings we have to get rid of */
            Textfile = regex_replace(Textfile, CommentLine, "");
            Textfile = regex_replace(Textfile, CommentStars, "");
            Textfile = regex_replace(Textfile, CommentInString, "'~/~*");
            Textfile = regex_replace(Textfile, CommentInComment, "' *~/':U"); 
            
            Textfile = regex_replace(Textfile, CommentBlock, "");
            Textfile = regex_replace(Textfile, CommentBlockRest, "");

            /* and things like this:                                                */
            /* with the first regex_replace the last bit of the following example a */
            /* DESIGN Window definition (used by the UIB)
                CREATE WINDOW Include ASSIGN
                        HEIGHT             = 6.52
                        WIDTH              = 51.4.
            /* END WINDOW DEFINITION */
            
            
            long size = Textfile.size();
            char* buffer = new char[size];
            TestfileOutput.write(Textfile.c_str(), sizeof(char) * Textfile.size());
            TestfileInput.close();
            TestfileOutput.close();
            return true;
        }
        else 
        {
            throw;
        }
    }
    catch (...)
    {
        TestfileInput.close();
        TestfileOutput.close();
        cout  << "error";
        return false;
    }
}

int main(int argc, char* argv[])
//int main()
{
    bool noerror = false;
    if (argc > 0)
       noerror =  fnRemoveComments(argv[1], argv[2]);

   if (noerror == true) 
    cout << "done.";

}

