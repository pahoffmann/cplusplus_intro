#include <cstdlib>
#include <iostream>
#include <set>
#include <sstream>
#include <assert.h>

#include "SparseVector.hpp"


using namespace std;


// ----------------------------------------------------------------------

// Normally, this declaration would go in a separate header file.

class ErrorContext              // displays test results
{
public:
    ErrorContext(ostream &os);              // write header to stream
    void desc(const char *msg, int line);   // write line/description
    void desc(string msg, int line);
    void result(bool good);                 // write test result
    ~ErrorContext();                        // write summary info
    bool ok() const;                        // true iff all tests passed
    
private:
    ostream &os;                            // output stream to use
    int passed;                             // # of tests which passed
    int total;                              // total # of tests
    int lastline;                           // line # of most recent test
    set<int> badlines;                      // line #'s of failed tests
    bool skip;                              // skip a line before title?
};


// ----------------------------------------------------------------------

// Normally, these method implementations would go in a separate source file.

ErrorContext::ErrorContext(ostream &os)
  : os(os), passed(0), total(0), lastline(0), skip(false)
{
    os << "line: ";
    os.width(65);
    os.setf(ios::left, ios::adjustfield);
    os << "description" << " result" << endl;
    os.width(78);
    os.fill('~');
    os << "~" << endl;
    os.fill(' ');
    os.setf(ios::right, ios::adjustfield);
}


void ErrorContext::desc(const char *msg, int line)
{
    if (lastline != 0 || (*msg == '-' && skip))
    {
        os << endl;
    }
    
    os.width(4);
    os << line << ": ";
    os.width(65);
    os.setf(ios::left, ios::adjustfield);
    os << msg << " ";
    os.setf(ios::right, ios::adjustfield);
    os.flush();
    
    lastline = line;
    skip = true;
}




void ErrorContext::desc(string msg, int line)
{
    if ((lastline != 0) || ((msg[0] == '-') && skip))
    {
        os << endl;
    }
    
    os.width(4);
    os << line << ": ";
    os.width(65);
    os.setf(ios::left, ios::adjustfield);
    os << msg << " ";
    os.setf(ios::right, ios::adjustfield);
    os.flush();
    
    lastline = line;
    skip = true;
}


#define DESC(x) desc(x, __LINE__)  // ugly hack

void ErrorContext::result(bool good)
{
    if (good)
    {
        os << "ok";
        passed++;
    }
    else
    {
        os << "ERROR";
        badlines.insert(lastline);
    }
    
    os << endl;
    total++;
    lastline = 0;
}


ErrorContext::~ErrorContext()
{
    os << endl << "Passed " << passed << "/" << total << " tests." << endl
       << endl;
    
    if (badlines.size() > 0)
    {
        os << "For more information, please consult:" << endl;
        for (set<int>::const_iterator it = badlines.begin();
            it != badlines.end(); it++)
        {
            os << "  " << __FILE__ << ", line " << *it << endl;
        }
        os << endl;
        
        if (badlines.size() > 2)
        {
            os << "We recommend that you "
               << "fix the topmost failure before going on."
               << endl << endl;
        }
    }
}


bool ErrorContext::ok() const
{
    return passed == total;
}



/*=====================================================================
 * TEST FUNCTIONS START HERE.
 */


/**
 * These tests are primarily focused on the most basic functionality.
 * If the class doesn't pass these tests then it may not make sense
 * to go on, because any more sophisticated functionality will probably
 * run into the same problems that these tests expose.
 **/
void smoketest(ErrorContext &ec)
{
  bool pass;

  ec.DESC("--- Smoke-Tests:  These are really basic! ---");

  ec.DESC("one-arg constructor, size, destructor");

  for (int i = 0; i < 10; i++)
  {
    // Construct the SparseVector.  When block ends, destructor will
    //  be called.
    SparseVector sv(100);

    pass = (sv.getSize() == 100);
  }
  ec.result(pass);
  
  // Make sure it is really is a sparse data-type!
  ec.DESC("one-arg constructor, very large size");

  for (int i = 0; i < 10; i++)
  {
    // Construct the SparseVector.  When block ends, destructor will
    //  be called.
    SparseVector sv(100000000);

    pass = (sv.getSize() == 100000000);
  }
  ec.result(pass);
}


/**
 * Run the get/set element tests, some number of times.
 *
 * Preconditions:
 *   runs > 0
 **/
void getsetelem(ErrorContext &ec, int runs)
{
  bool pass;

  // Run at least once!!
  assert(runs > 0);

  ec.DESC("--- getelem/setelem access patterns ---");

  for (int run = 0; run < runs; run++)
  {
    /*
     * Try sets/gets that will append nodes to the internal linked-list.
     */

    ec.DESC("append pattern");

    {
      SparseVector sv(40);
      set<int> indexes;

      // Set values first.
      // NOTE:  Index values increase as i increases.
      for (int i = 0; i < 10; i++)
      {
        int idx = i * 4 + i % 3;

      sv.setElem(idx, 100 - 3 * i);
        indexes.insert(idx);
      }

      // Get values next.
      pass = true;
      for (int i = 0; i < 10; i++)
        pass = pass && (sv.getElem(i * 4 + i % 3) == 100 - 3 * i);

      // Finally, make sure all other values are reported as zero.
      // NOTE:  Don't trust sv.getSize() here.  :)
      for (int i = 0; i < 40; i++)
      {
        if (indexes.find(i) == indexes.end())
          pass = pass && (sv.getElem(i) == 0);
      }

      ec.result(pass);
    }
  
    /*
     * Try sets/gets that will prepend nodes to the internal linked-list.
     */

    ec.DESC("prepend pattern");

    {
      SparseVector sv(40);
      set<int> indexes;

      // Set values first.
      // NOTE:  Index values decrease as i increases.
      for (int i = 0; i < 10; i++)
      {
        int idx = 40 - i * 4 - i % 3 - 1;

        sv.setElem(idx, 50 - 3 * i);
        indexes.insert(idx);
      }

      // Get values next.
      pass = true;
      for (int i = 0; i < 10; i++)
        pass = pass && (sv.getElem(40 - i * 4 - i % 3 - 1) == 50 - 3 * i);

      // Finally, make sure all other values are reported as zero.
      // NOTE:  Don't trust sv.getSize() here.  :)
      for (int i = 0; i < 40; i++)
      {
        if (indexes.find(i) == indexes.end())
          pass = pass && (sv.getElem(i) == 0);
      }

      ec.result(pass);
    }

    /*
     * Try sets/gets that put nodes in various locations in the list.
     */

    ec.DESC("insert pattern");

    {
      SparseVector sv(40);
      set<int> indexes;

      // Drop a node at the beginning of the list, then one at the end.

      sv.setElem(1, -16);
      indexes.insert(1);

      sv.setElem(38, 22);
      indexes.insert(38);

      // Now dump some other values into the middle of the list,
      // in no particular order!

      for (int i = 0, index = 3; i < 10; i++)
      {
        indexes.insert(index);
        sv.setElem(index, 350 - 19 * i + index / 4);
        index = (index + 19 + i % 5) % 40;
      }

      // Look at the values in the sparse-vector, in the Same Fun Order!
      pass = true;

      pass = pass && (sv.getElem(1) == -16);
      pass = pass && (sv.getElem(38) == 22);

      for (int i = 0, index = 3; i < 10; i++)
      {
        pass = pass && (sv.getElem(index) == 350 - 19 * i + index / 4);
        index = (index + 19 + i % 5) % 40;
      }

      // Finally, make sure all other values are reported as zero.
      // NOTE:  Don't trust sv.getSize() here.  :)
      for (int i = 0; i < 40; i++)
      {
        if (indexes.find(i) == indexes.end())
          pass = pass && (sv.getElem(i) == 0);
      }

      ec.result(pass);
    }
  }
}


/**
 * These tests verify the correctness of the copy-constructor.
 **/
void copies(ErrorContext &ec, int runs)
{
  bool pass;

  /* NOTE:  The little index-series that I calculate repeats values
   *        after 15 iterations, so we can only try 15 values in the
   *        tests.  Otherwise a value gets set twice, and it's hard
   *        to check for accurate copies this way.
   */

  ec.DESC("--- Copy-Constructor Correctness ---");

  for (int run = 0; run < runs; run++)
  {
    SparseVector origSV(100);
    set<int> indexes;
    
    for (int i = 0, index = 8; i < 15; i++)
    {
      indexes.insert(index);
      origSV.setElem(index, i * 315 + index);
      index = (index + 43 + i % 6) % 100;
    }

    {
      ec.DESC("check copy correctness");

      SparseVector copySV = origSV;

      pass = true;

      // Check that the nonzero values are correct.
      for (int i = 0, index = 8; i < 15; i++)
      {
        pass = pass && (copySV.getElem(index) == (i * 315 + index));
        index = (index + 43 + i % 6) % 100;
      }

      // Make sure remaining values are 0.
      for (int i = 0; i < 100; i++)
      {
        if (indexes.find(i) == indexes.end())
          pass = pass && (copySV.getElem(i) == 0);
      }

      ec.result(pass);

      ec.DESC("make sure it's a deep copy...");

      // Modify the copy!  (Indexes are same.)
      for (int i = 0, index = 8; i < 15; i++)
      {
        copySV.setElem(index, i * 249 + index);
        index = (index + 43 + i % 6) % 100;
      }

      // Check original now, to make sure values didn't change.

      pass = true;
      
      // Check that nonzero values are correct.
      for (int i = 0, index = 8; i < 15; i++)
      {
        pass = pass && (origSV.getElem(index) == (i * 315 + index));
        index = (index + 43 + i % 6) % 100;
      }

      // Make sure remaining values are 0.
      for (int i = 0; i < 100; i++)
      {
        if (indexes.find(i) == indexes.end())
          pass = pass && (origSV.getElem(i) == 0);
      }

      ec.result(pass);
    }
  }
}


/**
 * These tests exercise the equality/inequality operators for the
 * SparseVector.  This includes the following kinds of tests:
 *
 *   - Test of equality/inequality against self
 *   - Test of equality/inequality against copy
 *   - Test of equality/inequality against another SparseVector,
 *     with some values set to nonzero then zero.
 **/
void equality(ErrorContext &ec)
{
  ec.DESC("--- Equality/Inequality Operations ---");

  // Set up simple SparseVector stuff for testing equality with.

  SparseVector sv(10);

  sv.setElem(3, 15);
  sv.setElem(2, 6);
  sv.setElem(8, -4);
  sv.setElem(0, 1);
  sv.setElem(5, -15);

  const SparseVector &csvRef = sv;

  ec.DESC("equality against self");

  // This won't compile if operator==() isn't declared const.
  ec.result(csvRef == sv);

  ec.DESC("inequality against self");

  // This won't compile if operator!=() doesn't take a const-reference.
  ec.result(!(sv != csvRef));

  ec.DESC("equality/inequality against identical copy");

  // Invoke copy-constructor.
  // This won't compile if copy-constructor doesn't take a const-reference.
  const SparseVector copySV = csvRef;

  ec.result((csvRef == copySV) && !(copySV != csvRef));

  ec.DESC("equality/inequality against modified copy");
  {
    // Now make a copy and then modify it, and see if things work correctly.

    SparseVector diffSV = csvRef;
    diffSV.setElem(8, 0);      // Zero out one of the elements!

    ec.result((diffSV != sv) && !(csvRef == diffSV));
  }

  ec.DESC("equality/inequality against similar SparseVector");
  {
    // Create a similar version of the original SparseVector, and see if
    // it still works.  (This could fail, if the SparseVector doesn't handle
    // 0 elements properly.)

    SparseVector almostSV(10);

    almostSV.setElem(8, -4);
    almostSV.setElem(5, -15);
    almostSV.setElem(4, 38);    // Set element 4...
    almostSV.setElem(3, 15);
    almostSV.setElem(4, 0);     // ...then clear it.
    almostSV.setElem(0, 1);
    almostSV.setElem(2, 6);

    ec.result((almostSV == sv) && !(csvRef != almostSV));
  }

  ec.DESC("equality/inequality against different-size empty SparseVector");
  {
    SparseVector oneSizeSV(5);
    SparseVector otherSizeSV(7);

    ec.result(!(oneSizeSV == otherSizeSV) && (otherSizeSV != oneSizeSV));
  }
}


/**
 * This test exercises the assignment operator, one or more times.
 **/
void assignment(ErrorContext &ec, int runs)
{
  bool pass;

  /* NOTE:  The little index-series that I calculate repeats values
   *        after 15 iterations, so we can only try 15 values in the
   *        tests.  Otherwise a value gets set twice, and it's hard
   *        to check for accurate copies this way.
   */

  ec.DESC("--- Assignment Correctness ---");

  for (int run = 0; run < runs; run++)
  {
    SparseVector origSV(100);
    set<int> indexes;
    
    for (int i = 0, index = 8; i < 15; i++)
    {
      indexes.insert(index);
      origSV.setElem(index, i * 315 + index);
      index = (index + 43 + i % 6) % 100;
    }

    {
      ec.DESC("check assigned-copy correctness");

      // Initialize new sparse-vector, same size as original!
      SparseVector copySV(100);

      // Put some values into the copy...
      for (int i = 0, index = 8; i < 15; i++)
      {
        copySV.setElem(index, i * 203 - index);
        index = (index + 46 + i % 5) % 100;
      }

      // Assign the original to the copy!  This should overwrite the
      // values in the copy.
      copySV = origSV;

      pass = true;
      
      // Verify that the nonzero values are correct.
      for (int i = 0, index = 8; i < 15; i++)
      {
        pass = pass && (copySV.getElem(index) == (i * 315 + index));
        index = (index + 43 + i % 6) % 100;
      }

      // Check the rest of the values to ensure they are zero.
      for (int i = 0; i < 100; i++)
      {
        if (indexes.find(i) == indexes.end())
          pass = pass && (copySV.getElem(i) == 0);
      }

      ec.result(pass);

      ec.DESC("make sure it's a deep copy...");

      for (int i = 0, index = 8; i < 15; i++)
      {
        copySV.setElem(index, i * 249 + index);
        index = (index + 43 + i % 6) % 100;
      }

      // Check original now, to make sure values didn't change.

      pass = true;

      // Verify that the nonzero values are correct.
      for (int i = 0, index = 8; i < 15; i++)
      {
        pass = pass && (origSV.getElem(index) == (i * 315 + index));
        index = (index + 43 + i % 6) % 100;
      }

      // Check the rest of the values to ensure they are zero.
      for (int i = 0; i < 100; i++)
      {
        if (indexes.find(i) == indexes.end())
          pass = pass && (origSV.getElem(i) == 0);
      }

      ec.result(pass);
    }

    ec.DESC("check self-assignment");
    {
      SparseVector cpSV = origSV;

      cpSV = cpSV = cpSV = cpSV = cpSV;

      pass = true;

      // Verify that the nonzero values are correct.
      for (int i = 0, index = 8; i < 15; i++)
      {
        pass = pass && (cpSV.getElem(index) == (i * 315 + index));
        index = (index + 43 + i % 6) % 100;
      }

      // Check the rest of the values to ensure they are zero.
      for (int i = 0; i < 100; i++)
      {
        if (indexes.find(i) == indexes.end())
          pass = pass && (cpSV.getElem(i) == 0);
      }

      ec.result(pass);
    }
  }
}




/**
 * This program is a simple test-suite for the SparseVector class.  As the
 * name indicates, the SparseVector represents a vector of integers where
 * many of the values are expected to be zero.  Thus, only the nonzero
 * values are represented within instances of the class.
 **/
int main()
{
  cout << "Testing the SparseVector!!" << endl << endl;

  cout << "NOTE:  If you see any memory errors, you MUST fix them!" << endl;
  cout << "       Tests intentionally invoke destructors after they complete,"
       << endl;
  cout << "       so if you see a seg-fault after a passed test, it is"
       << endl;
  cout << "       probably a bug in your destructor." << endl;

  cout << endl;

  ErrorContext ec(cout);

  smoketest(ec);        // Simple smoke-test that does MOST BASIC tests.

  getsetelem(ec, 4);    // Complex getelem/setelem access patterns.

  copies(ec, 4);        // Check copy-constructor.

  assignment(ec, 4);    // Check assignment operator.

  equality(ec);         // Checks for == / != operators.
 
}

