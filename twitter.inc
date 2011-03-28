<?php

function curl($url) {
        $ch = curl_init();

        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; ICS)");
        $output = curl_exec($ch);
        curl_close($ch);

	return $output;
}

function getProfileByName($screenname) {
  return getProfileByUrl('https://api.twitter.com/1/users/show.json?screen_name='.$screenname);
}

function getProfileById($id) {
  return getProfileByUrl('https://api.twitter.com/1/users/show.json?user_id='.$id);
}

function profile($screenname) {
  return getProfileByName($screenname);
}

function getProfileByUrl($url) {
  $profile=json_decode(curl($url));

  if(!isset($profile->screen_name)) return "";

  $rv= '<Entity Type="maltego.affiliation.Twitter">'."\n";
  $rv.= ' <Value>'.$profile->screen_name.'</Value>'."\n";
  $rv.= " <AdditionalFields>\n";
 

/*
    [contributors_enabled] => 
    [following] => 
    [time_zone] => Hawaii
    [profile_text_color] => 333333
    [description] => 
    [status] => stdClass Object
        (
            [text] => is this a major problem for wheelchair users? it is not something that seems that prevalent
            [id_str] => 9326720817565696
            [truncated] => 
            [source] => web
            [favorited] => 
            [geo] => 
            [created_at] => Mon Nov 29 19:23:58 +0000 2010
            [place] => 
            [in_reply_to_screen_name] => 
            [in_reply_to_status_id] => 
            [in_reply_to_status_id_str] => 
            [contributors] => 
            [coordinates] => 
            [retweeted] => 
            [in_reply_to_user_id] => 
            [id] => 9326720817565696
            [in_reply_to_user_id_str] => 
            [retweet_count] => 0
        )

    [default_profile_image] => 1
    [statuses_count] => 46
    [profile_sidebar_fill_color] => DDEEF6
    [url] => 
    [profile_image_url] => http://a2.twimg.com/sticky/default_profile_images/default_profile_1_normal.png
    [id_str] => 221076591
    [profile_background_tile] => 
    [friends_count] => 12
    [location] => 
    [screen_name] => GroupPMC
    [default_profile] => 1
    [follow_request_sent] => 
    [profile_link_color] => 0084B4
    [followers_count] => 8
    [lang] => en
    [created_at] => Mon Nov 29 17:36:50 +0000 2010
    [profile_sidebar_border_color] => C0DEED
    [notifications] => 
    [protected] => 
    [is_translator] => 
    [verified] => 
    [profile_use_background_image] => 1
    [name] => James and co
    [listed_count] => 0
    [profile_background_color] => C0DEED
    [id] => 221076591
    [show_all_inline_media] => 
    [geo_enabled] => 
    [profile_background_image_url] => http://a3.twimg.com/a/1301071706/images/themes/theme1/bg.png
    [utc_offset] => -36000
    [favourites_count] => 0
)
*/
 
  $rv.= '  <Field Name="affiliation.profile-url" DisplayName="Profile URL" MatchingRule="strict">http://twitter.com/'.$profile->screen_name.'</Field>'."\n";
  $rv.= '  <Field Name="affiliation.uid" DisplayName="UID" MatchingRule="strict">'.$profile->screen_name.'</Field>'."\n";
  $rv.= '  <Field Name="affiliation.screen-name" DisplayName="Screen Name">'.$profile->screen_name.'</Field>'."\n";
  $rv.= '  <Field Name="twitter.friendcount" DisplayName="Friend Count">'.$profile->friends_count.'</Field>'."\n";
  $rv.= '  <Field Name="person.fullname" DisplayName="Real Name">'.$profile->name.'</Field>'."\n";

  $rv.= " </AdditionalFields>\n";
  $rv.= ' <IconURL>'.$profile->profile_image_url.'</IconURL>'."\n";
  $rv.= '</Entity>'."\n";
  
  return $rv;
}

?>
