#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VERSION "1.00"

const char *program_name;   /* the name by which we were called */

static void
usage(int exitcode, const char *what)
{
  FILE *f=stdout;

  if (exitcode)
  {
    if (what)
      fprintf(stderr, "%s: %s\n",program_name,what);
    fprintf (stderr, "Try `%s --help' for more information.\n", program_name);
    exit(exitcode);
  }

  fprintf(f, "%s version %s\n", program_name, VERSION);

  fprintf(f, "Usage: %s [-l:dxn:b:h] ANGLE_DEGREE\n", program_name);
  fputs("Moter test tool\n", f);
  fputs((
"  ANGLE_DEGREE    : move position to ANGLE_DEGREE with enable motor torque, -50.0~50.0\n"
"  -l TORQUE_LIMIT : set motor torque limit to TORQUE_LIMIT, 0~1023, default=200\n"
"  -d              : disable moter torque\n"
"  -x              : disable display status\n"
"  -n PORT_NAME    : set serial port name tp PORT_NAME, default=/dev/ttyS3\n"
"  -b BAUD_RATE    : set serial baud rate to BAUD_RATE, default=57600\n"
"  -h              : display usage\n"
    ), f);
  exit(exitcode);
}

static void
chkinvok(const char *s)
{
  const char *p;

  p = s;
  while (*p == '-')
    s = ++p;
  while (*p)
    if (*p++ == '/')
      s = p;
  program_name = s;
}

int
main (int argc, char **argv)
{
  int lflag = 0;
  int dflag = 0;
  int xflag = 0;
  int nflag = 0;
  int bflag = 0;
  char *lvalue = NULL;
  char *nvalue = NULL;
  char *bvalue = NULL;
  int index;
  int c;

  chkinvok(argv[0]);

  opterr = 0;

  while ((c = getopt (argc, argv, "l:dxn:b:h")) != -1)
    switch (c)
      {
      case 'l':
        lflag = 1;
        lvalue = optarg;
        break;
      case 'd':
        dflag = 1;
        break;
      case 'x':
        xflag = 1;
        break;
      case 'n':
        nflag = 1;
        nvalue = optarg;
        break;
      case 'b':
        bflag = 1;
        bvalue = optarg;
        break;
      case 'h':
        usage(0, NULL);
        break;
      case '?':
        if (optopt == 'l')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (optopt == 'n')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (optopt == 'b')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        usage(0, NULL);
        return 1;
      default:
        abort ();
      }

  printf ("lflag = %d, lvalue = %s\n",
          lflag, lvalue);

  printf ("dflag = %d, xflag = %d\n",
          dflag, xflag);

  printf ("nflag = %d, nvalue = %s\n",
          nflag, nvalue);

  printf ("bflag = %d, bvalue = %s\n",
          bflag, bvalue);

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);

  return 0;
}

