/* Rule 20.14 BAD: this #endif closes an #if that was opened in the file
 * that includes this header. The structure only makes sense if you read
 * both files together. */
#endif
