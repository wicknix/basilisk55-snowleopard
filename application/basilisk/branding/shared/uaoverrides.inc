#define GUAO_PREF general.useragent.override

#define UXP_VERSION @MOZILLA_UAVERSION_U@
#define UXP_VERSION_SLICE Goanna/102.0
#define UXP_DATE_SLICE Goanna/20170101
#define APP_SLICE Basilisk/@MOZ_APP_VERSION@

#define GK_VERSION 55.9
#define GK_SLICE Gecko/20100101
#define FX_SLICE Firefox/102.0

#define PALE_MOON_VERSION 32.4.1
#define PALE_MOON_SLICE PaleMoon/@PALE_MOON_VERSION@

// Macintosh; Intel Mac OS X 10.11; macro is resolved at runtime, see MoonchildProductions/UXP/issues/1473

// Special-case AMO
// We send the native UA slice now, since they no longer offer any compatible extensions for us.
// This will result in an "only with Firefox" message which suits us fine, because it's the truth.
pref("general.useragent.override.addons.mozilla.org","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");

// Required for domains that are unresponsive to requests from users (or likely to be)
pref("general.useragent.override.aol.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0 (Basilisk)");
pref("general.useragent.override.bing.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0 (Basilisk)");
pref("general.useragent.override.chase.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0");
pref("general.useragent.override.dropbox.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:68.9) Gecko/20100101 Firefox/68.9 (Basilisk)");
pref("general.useragent.override.instagram.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:68.0) Gecko/20100101 Firefox/68.0");
pref("general.useragent.override.gstatic.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:71.0) Gecko/20100101 Firefox/71.0 Basilisk/20240101");
pref("general.useragent.override.kroger.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:86.0) Gecko/20100101 Firefox/86.0 (Basilisk)");
pref("general.useragent.override.live.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0 (Basilisk)");
pref("general.useragent.override.msn.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0 (Basilisk)");
pref("general.useragent.override.netteller.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0");
pref("general.useragent.override.patientaccess.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:60.0) Gecko/20100101 Firefox/60.0 Basilisk/20240101");
pref("general.useragent.override.outlook.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0 (Basilisk)");
pref("general.useragent.override.vimeo.com", "Mozilla/5.0 (iPhone; CPU iPhone OS 15_5 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) EdgiOS/102.0.1245.30 Version/15.0 Mobile/15E148 Safari/604.1");
pref("general.useragent.override.web.de","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0 (Basilisk)");
pref("general.useragent.override.yahoo.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:99.9) Gecko/20100101 Firefox/99.9");
pref("general.useragent.override.calendar.yahoo.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0 (Basilisk)");
pref("general.useragent.override.facebook.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:52.0) Gecko/20100101 Firefox/52.0 Basilisk/20240101");

// Soundcloud uses Firefox-exclusive combinations of code. Never pass Firefox slice.
pref("general.useragent.override.soundcloud.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");
pref("general.useragent.override.players.brightcove.net","Mozilla/5.0 (Windows NT 6.1; Trident/7.0; rv:11.0) like Gecko");
// Google fonts serves physically different fonts to later Firefox versions that render incorrectly unless on Gecko
pref("general.useragent.override.fonts.googleapis.com", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:61.9) Gecko/20100101 Firefox/61.9");
pref("general.useragent.override.fonts-api.wp.com", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:61.9) Gecko/20100101 Firefox/61.9");

// The following requires native mode. Or it blocks.. "too old firefox", breakage, etc.
pref("general.useragent.override.deviantart.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");
pref("general.useragent.override.deviantart.net","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");
pref("general.useragent.override.altibox.dk","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");
pref("general.useragent.override.altibox.no","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");
pref("general.useragent.override.firefox.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");
pref("general.useragent.override.mozilla.org","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");
pref("general.useragent.override.mozilla.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");
pref("general.useragent.override.github.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");
pref("general.useragent.override.zoho.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Goanna/20170101 Basilisk/20240101");

// UA-Sniffing domains below have indicated no interest in supporting Basilisk (BOO!)
pref("general.useragent.override.humblebundle.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0 (Basilisk)");
pref("general.useragent.override.privat24.ua","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:38.0) Gecko/20100101 Firefox/38.0");
pref("general.useragent.override.citi.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:68.0) Gecko/20100101 Firefox/68.0 SeaMonkey/2.53.12");
pref("general.useragent.override.facebook.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:68.0) Gecko/20100101 Firefox/68.0 Basilisk/20240101");
pref("general.useragent.override.mewe.com", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0");

// UA-sniffing domains that are "app/vendor-specific" and do not like Basilisk
pref("general.useragent.override.web.whatsapp.com","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77 Safari/537.36");

// The following domains do not like the Goanna slice
pref("general.useragent.override.bab.la","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0");
pref("general.useragent.override.babla.gr","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0");
pref("general.useragent.override.collinsdictionary.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0");
pref("general.useragent.override.dictionary.cambridge.org","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0");
pref("general.useragent.override.hitbox.tv","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0");
pref("general.useragent.override.ldoceonline.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0");
pref("general.useragent.override.yuku.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0 Basilisk/20240101");

// Domains Basilisk overrides that are not in the Pale Moon overrides
pref("general.useragent.override.twitter.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Firefox/102.0 Basilisk/20240101");
pref("general.useragent.override.slack.com","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:120.0) Gecko/20100101 Firefox/120.0 Basilisk/20240101");
// There are multiple addons on the Pale Moon addons site that work with Basilisk that are not listed on the Basilisk addons site.
pref("general.useragent.override.addons.palemoon.org","Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:102.0) Gecko/20100101 Goanna/102.0 Firefox/102.0 PaleMoon/33.0.0");

// ============================================================================
