#!/usr/bin/env rspec

require_relative "../test_helper"
require "ystorage/snapshots_finish"

describe Yast::YStorage::SnapshotsFinish do
  describe "#write" do
    before do
      allow(subject).to receive(:second_stage_required?).and_return(second_stage_required)
      allow(Yast2::FsSnapshot).to receive(:configured?).and_return(snapper_configured)
    end

    context "when second stage is required" do
      let(:second_stage_required) { true }

      context "when snapper is configured" do
        let(:snapper_configured) { true }

        it "does not create any snapshot" do
          expect(Yast2::FsSnapshot).to_not receive(:create_single)
          expect(subject.write).to eq(false)
        end
      end

      context "when snapper is not configured" do
        let(:snapper_configured) { false }

        it "does not create any snapshot" do
          expect(Yast2::FsSnapshot).to_not receive(:create_single)
          expect(subject.write).to eq(false)
        end
      end
    end

    context "when second stage isn't required" do
      let(:second_stage_required) { false }

      context "when snapper is configured" do
        let(:snapper_configured) { true }

        context "when upgrading" do
          before do
            allow(Yast::Mode).to receive(:update).and_return(true)
          end

          it "creates a snapshot of type 'post' with 'after upgrade' as description and paired with 'pre' snapshot" do
            expect(Yast2::FsSnapshotStore).to receive(:load).and_return(1)
            expect(Yast2::FsSnapshotStore).to receive(:clean)
            expect(Yast2::FsSnapshot).to receive(:create_post).with("after upgrade", 1).and_return(true)
            expect(subject.write).to eq(true)
          end
        end

        context "when installing" do
          before do
            allow(Yast::Mode).to receive(:update).and_return(false)
          end

          it "creates a snapshot of type 'single' with 'after installation' as description" do
            expect(Yast2::FsSnapshot).to receive(:create_single).with("after installation").and_return(true)
            expect(subject.write).to eq(true)
          end
        end
      end

      context "when snapper is not configured" do
        let(:snapper_configured) { false }

        it "does not create any snapshot" do
          expect(Yast2::FsSnapshot).to_not receive(:create_single)
          expect(subject.write).to eq(false)
        end
      end
    end
  end
end