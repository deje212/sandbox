#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/valid.h>
#include <libxml/xmlschemas.h>

unsigned long get_file_size(const char *file_name) 
{
  struct stat buf;

  if ( stat(file_name, &buf) != 0 ) 
    return 0;

  return (unsigned long)buf.st_size;
}

void handleValidationError(void *ctx, const char *format, ...) 
{
  char *errMsg;
  va_list args;

  va_start(args, format);
  vasprintf(&errMsg, format, args);
  va_end(args);

  fprintf(stderr, "Validation Error: %s", errMsg);

  free(errMsg);
}

int main(int argc, const char * argv[]) 
{
  unsigned long xmlLength;
  char *xmlSource;
  FILE *fp;
  int result;

  if (argc != 3)
  {
    fprintf(stderr, "Usage: check <schema> <xml>\n");
    return EXIT_FAILURE;
  }

  /* argv[1] = xsd path, argv[2] = xml path. */

  printf("XSD File: %s\n", argv[1]);
  printf("XML File: %s\n", argv[2]);

  if ((xmlLength = get_file_size(argv[2])) == 0)
  {
    fprintf(stderr, "XML file is empty?!");
    return EXIT_FAILURE;
  }

  if ((xmlSource = (char *)malloc(sizeof(char) * (xmlLength + 1))) == NULL)
  {
    fprintf(stderr, "Error allocating buffer for xml file.\n");
    return EXIT_FAILURE;
  }

  fp = fopen(argv[2], "r");
  result = 42;

  if (fp == NULL || (fread(xmlSource, xmlLength, 1, fp) <= 0))
  {
    fprintf(stderr, "Error reading xml file.\n");
    fclose(fp);
    return EXIT_FAILURE;
  }

  *(xmlSource + xmlLength) = '\0';

  printf("XML Source:\n\n%s\n\n", xmlSource);
  fclose(fp);

  xmlSchemaParserCtxtPtr parserCtx = NULL;
  xmlSchemaPtr schema = NULL;
  xmlSchemaValidCtxtPtr validCtx = NULL;
  xmlDocPtr xmlDocumentPointer;

  if ((xmlDocumentPointer = xmlParseMemory(xmlSource, xmlLength)) == NULL)
  {
    fprintf(stderr, "Error parsing xml file.\n");
    return EXIT_FAILURE;
  }

  if ((parserCtx = xmlSchemaNewParserCtxt(argv[1])) == NULL) 
  {
    fprintf(stderr, "Could not create XSD schema parsing context.\n");
    goto leave;
  }

  if ((schema = xmlSchemaParse(parserCtx)) == NULL) 
  {
    fprintf(stderr, "Could not parse XSD schema.\n");
    goto leave;
  }

  if ((validCtx = xmlSchemaNewValidCtxt(schema)) == NULL) 
  {
    fprintf(stderr, "Could not create XSD schema validation context.\n");
    goto leave;
  }

  /* xmlSchemaValidateDoc error functions. */
  xmlSetStructuredErrorFunc(NULL, NULL);
  xmlSetGenericErrorFunc(NULL, handleValidationError);
  xmlThrDefSetStructuredErrorFunc(NULL, NULL);
  xmlThrDefSetGenericErrorFunc(NULL, handleValidationError);

  result = xmlSchemaValidateDoc(validCtx, xmlDocumentPointer);

leave:
  if (parserCtx) 
    xmlSchemaFreeParserCtxt(parserCtx);

  if (schema)
    xmlSchemaFree(schema);

  if (validCtx) 
    xmlSchemaFreeValidCtxt(validCtx);

  printf("Validation successful: %s (result: %d)\n", (result == 0) ? "YES" : "NO", result);

  return EXIT_SUCCESS;
}
