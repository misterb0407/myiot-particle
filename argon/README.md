Consult https://docs.particle.io/tutorials/developer-tools/cli/ for development
setup.

install CLI
$ bash <( curl -sL https://particle.io/install-cli )

update
$ particle update-cli

setup credential
$ particle setup

create project
$ particle project create

compile in cloud, anything in 'src' will be sent and compiled
$ particle compile argon

search available library (e.g. any library name containing 'internet'
$ particle library search internet

to add found library (e.g. found InternetButton), verify this is accounte in
project.properties
$ particle library add InternetButton

to download library into project folder (consume space in project space)
$ particle library copy InternetButton

to download source of new added library in properties (but not added physically
to project space, it will be linked during 'cloud-compile'
$ particle library view InternetButton



