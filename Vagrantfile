Vagrant.configure("2") do |config|
  config.vm.box = "bento/ubuntu-20.04"
  config.vm.provision "shell", :path => "misc/provision.sh", :privileged => false

  config.vm.define :server do |s|
    s.vm.hostname = "server"
    s.vm.network :private_network, ip: "192.168.0.3", virtualbox__intnet: "intnet"
  end

end
