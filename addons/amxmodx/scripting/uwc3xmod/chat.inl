
public InitHud()
{
	hudchat_init();
	hudchat_set_color(178, 14, 41);
	hudchat_set_removetime(1.7);
	hudchat_set_channel(5);
	return;
}

public EndHud()
{
	hudchat_end();
	return;
}
