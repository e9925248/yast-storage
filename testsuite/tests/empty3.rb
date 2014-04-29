# encoding: utf-8

# testedfiles: helper1b.yh
module Yast

  class TestClient < Client

    def main
      Yast.include self, "setup-system.rb"

      setup_system("empty")

      Yast.include self, "helper1a.rb"

      Yast.import "ProductFeatures"

      ProductFeatures.SetBooleanFeature("partitioning", "try_separate_home", false)
      ProductFeatures.SetBooleanFeature("partitioning", "proposal_lvm", true)
      ProductFeatures.SetBooleanFeature("partitioning", "proposal_snapshots", false)
      ProductFeatures.SetBooleanFeature("partitioning", "vm_keep_unpartitioned_region", true)
      ProductFeatures.SetStringFeature("partitioning", "vm_desired_size", "30 GB")
      ProductFeatures.SetStringFeature("partitioning", "root_base_size", "20 GB")

      def setup3()
      end

      Yast.include self, "helper1b.rb"

      nil
    end

  end

end

Yast::TestClient.new.main
