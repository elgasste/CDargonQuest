#include "string_util.h"

const char* dqStringUtil_GetIndefiniteArticleText( dqIndefiniteArticle_t article, sfBool upperCase )
{
   switch ( article )
   {
      case dqIndefiniteArticleA:
         return upperCase ? STR_INDEFINITE_ARTICLE_A_UPPER : STR_INDEFINITE_ARTICLE_A_LOWER;
      case dqIndefiniteArticleAn:
         return upperCase ? STR_INDEFINITE_ARTICLE_AN_LOWER : STR_INDEFINITE_ARTICLE_AN_LOWER;
      default:
         return "";
   }
}
