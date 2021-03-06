# encoding: utf-8

# testedfiles: helper.rb

module Yast

  class TestClient < Client

    def main

      def setup1()
        setup_system("empty-ppc64le")

        # TODO: The PReP partition is ignored since partitions without a mount
        # point are ignored when reading the flex proposal configuration.

        setup_part_info(<<-EOT)
PARTITION  mount=       size=8MB
PARTITION  mount=/      size=8GB
PARTITION  mount=swap   size=1GB
PARTITION  mount=/data  sizepct=100
EOT
      end

      def setup2()
      end

      def setup3()
      end

      Yast.include self, "helper.rb"

    end

  end

end

Yast::TestClient.new.main
