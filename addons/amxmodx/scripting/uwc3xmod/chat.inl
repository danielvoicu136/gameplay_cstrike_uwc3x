

public InitHud()
{
	hudchat_init();
	return;
}

public EndHud()
{
	hudchat_end();
	return;
}

public HudChatShow(id, const msg[], any:...)
{
	hudchat_set_color(178, 14, 41);
	hudchat_set_removetime(1.7);
	hudchat_set_channel(5);

	// notice I used "id" instead of "LANG_PLAYER"
	// that is the proper way to do ML for a specific player
	// only use "LANG_PLAYER" when using all players (0)

	new message[__HUDCHAT_MAXMSGLEN];
	vformat(message, charsmax(message), msg, 3);

	hudchat_show(id, "%L", id, message);
	hudchat_update();
	return;
}