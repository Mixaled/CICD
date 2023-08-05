#!/bin/bash
STAGE=$CI_JOB_STAGE
STATUS=$CI_JOB_STATUS
API_TOKEN="6020604601:AAEGX9brMVPvFmYA2fK7zpfr6TYd6543FkE"
CHAT_ID="6218011480"
MESSAGE="Pipiline: $STAGE Status: $STATUS"
curl -s -X POST https://api.telegram.org/bot$API_TOKEN/sendMessage -d chat_id=$CHAT_ID -d text="$MESSAGE"