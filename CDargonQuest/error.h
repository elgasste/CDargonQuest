#if !defined( DQ_ERROR_H )
#define DQ_ERROR_H

void dqError_Message( const char* message );
void dqError_ExitWithMessage( const char* message );
void dqError_ExitWithMessageNoLog( const char* message );

#endif
